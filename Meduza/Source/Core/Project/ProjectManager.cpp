#include "MePCH.h"
#include "Core/Project/ProjectManager.h"

#include "Platform/General/FileSystem/FileSystem.h"
#include "Core/Serialization/Serializer.h"

constexpr char* gc_projectPrefix = ".Project";
constexpr char* gc_scriptPrefix = ".Script";

constexpr char* gc_projectName = "#ProjectName";
constexpr char* gc_scriptConfig = "#ScriptConfig";
constexpr char* gc_startUpScene = "#StartupScene";

Me::Project::ProjectManager::ProjectManager()
{
	//Check if there is a startup file if so load project the project Specified
	LoadProject("Projects/Megaman/Config/.ProjectMegaman.mec");
}

Me::Project::ProjectManager::~ProjectManager()
{

}

void Me::Project::ProjectManager::LoadProject(std::string const& a_path)
{
	//Load out the file
	std::string configFile = Files::FileSystem::ReadFile(a_path);

	std::string projectName = Files::FileSystem::GetFromToken(configFile, gc_projectName);
	std::string scriptConfig = Files::FileSystem::GetFromToken(configFile, gc_scriptConfig);
	std::string startupScene = Files::FileSystem::GetFromToken(configFile, gc_startUpScene);

	Serialization::Serializer::GetInstance()->DeserializeScene(startupScene);
}

void Me::Project::ProjectManager::CreateProject(std::string const& a_name)
{
	std::string projectName = gc_projectPrefix;
	projectName.append(a_name);
	projectName.append(".mec");

	std::string scriptName = gc_scriptPrefix;
	scriptName.append(a_name);
	scriptName.append(".mec");

	std::string projectPath = "Projects/";
	projectPath.append(a_name);
	projectPath.append("/Config/");

	std::string assetPath = "Projects/";
	assetPath.append(a_name);
	assetPath.append("/Assets/");

	std::string scenePath;

	if (!Files::FileSystem::DoesFileExist(projectPath + projectName))
	{
		Files::FileSystem::CreateNewFile(projectName, projectPath);
		Files::FileSystem::CreateNewFile(scriptName, projectPath);
		scenePath = Files::FileSystem::CreateNewFile("NewScene.scene", assetPath + "Scenes");
		//Create Scene
		Serialization::Serializer::GetInstance()->SerializeSceneAs(scenePath);
	}
	else
	{
		LoadProject(projectPath + projectName);
		return;
	}
	std::ofstream configFile;
	configFile.open(projectPath + projectName);
	configFile << gc_projectName << " " << a_name << " \n";
	configFile << "\n";
	configFile << gc_scriptConfig << " " << projectPath << scriptName << " \n";
	configFile << "\n";
	configFile << gc_startUpScene << " " << scenePath << " \n";
	configFile << "\n";

	configFile.close();
	LoadProject(projectPath + projectName);
}