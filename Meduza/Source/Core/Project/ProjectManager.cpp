#include "MePCH.h"
#include "Core/Project/ProjectManager.h"

#include "Platform/General/FileSystem/FileSystem.h"
#include "Core/Serialization/Serializer.h"
#include "Platform/General/ResourceLibrary.h"
#include "Platform/General/Graphics/RenderLayer.h"
#include "Core/Scripting/ScriptConfig.h"

constexpr char* gc_projectPrefix = ".Project";
constexpr char* gc_scriptPrefix = ".Script";

constexpr char* gc_projectName = "#ProjectName";
constexpr char* gc_scriptConfig = "#ScriptConfig";
constexpr char* gc_startUpScene = "#StartupScene";


Me::Project::ProjectManager* Me::Project::ProjectManager::ms_instance = nullptr;

Me::Project::ProjectManager* Me::Project::ProjectManager::CreateProjectManager()
{
	if (ms_instance != nullptr)
	{
		ME_CORE_ASSERT_M(true , "Can't have multiple instanced of the projectManager!")
	}

	return new ProjectManager();
}

Me::Project::ProjectManager::ProjectManager()
{
	ms_instance = this;
	//Check if there is a startup file if so load project the project Specified

	//LoadProject("Projects/Megaman/Config/.ProjectMegaman.mec");
}

Me::Project::ProjectManager::~ProjectManager()
{
	ms_instance = nullptr;
}

void Me::Project::ProjectManager::LoadProject(std::string const& a_path)
{
	//Load out the file
	Resources::ResourceLibrary::GetInstance()->Cleanup(true);
	Renderer::RenderLayer::GetRenderLayer()->Init();

	std::string configFile = Files::FileSystem::ReadFile(a_path);

	std::ifstream is(a_path.c_str());
	is.open(a_path);

	if (!is.is_open())
	{
		ME_LOG("Can't Open File! \n");
	}

	cereal::XMLInputArchive archive(is);

	std::string scriptConfig; 
	std::string startupScene;

	archive.setNextName("Project");
	archive.startNode();

	archive(cereal::make_nvp(gc_projectName, m_projectName));
	archive(cereal::make_nvp(gc_scriptConfig, scriptConfig));
	archive(cereal::make_nvp(gc_startUpScene, startupScene));

	archive.finishNode();

	std::string assetPath = "Projects/";
	assetPath.append(m_projectName);
	assetPath.append("/Assets");

	m_assetBrowserBase = assetPath;

	if (Scripting::ScriptConfig::GetScriptConfig()->LoadScriptConfig(scriptConfig, m_projectName, assetPath))
	{

	}

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
	assetPath.append("/Assets");

	std::string scenePath;

	if (!Files::FileSystem::DoesFileExist(projectPath + projectName))
	{
		Resources::ResourceLibrary::GetInstance()->Cleanup(true);
		Renderer::RenderLayer::GetRenderLayer()->Init();

		Files::FileSystem::CreateNewFile(projectName, projectPath);
		Files::FileSystem::CreateNewFile(scriptName, projectPath);
		scenePath = Files::FileSystem::CreateNewFile("NewScene.scene", assetPath + "/Scenes");
		//Create Scene
		Serialization::Serializer::GetInstance()->SerializeSceneAs(scenePath);
	}
	else
	{
		LoadProject(projectPath + projectName);
		return;
	}

	std::string newProjectPath = projectPath + projectName;
	std::string newScriptPath = projectPath + scriptName;

	std::ofstream configFile(newProjectPath.c_str());

	cereal::XMLOutputArchive archiveProject(configFile);

	archiveProject.setNextName("Project");
	archiveProject.startNode();

	archiveProject(cereal::make_nvp(gc_projectName, a_name));
	archiveProject(cereal::make_nvp(gc_scriptConfig, newScriptPath));
	archiveProject(cereal::make_nvp(gc_startUpScene, scenePath));

	archiveProject.finishNode();

	m_projectName = projectName;
	m_assetBrowserBase = assetPath;

	if (Scripting::ScriptConfig::GetScriptConfig()->InitializeScriptConfig(newScriptPath, a_name))
	{

	}
}