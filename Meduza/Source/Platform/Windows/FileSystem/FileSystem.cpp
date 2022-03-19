#include "MePCH.h"
#include "Platform/Windows/FileSystem/FileSystem.h"

#include <filesystem>
#include "Platform/General/Resources/Resource.h"

#include "Core/Project/ProjectManager.h"

void Me::Files::Windows::FileSystem::OpenFolder(std::string const& a_path)
{
	std::string folderPath = a_path;
	std::replace(folderPath.begin(), folderPath.end(), '/', '\\');

	std::string pathToOpen = FindFullPath();
	pathToOpen.append(folderPath);

	std::string openCommand = "explorer ";
	openCommand.append(pathToOpen);

	system(openCommand.c_str());
	
}

std::string Me::Files::Windows::FileSystem::FindFullPath()
{
	char path[256];
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, path, (sizeof(path)));

	std::string fullPath = path;
	size_t pos = fullPath.find("Sandbox.exe"); //find location of word
	fullPath.erase(pos, fullPath.size() - pos); //delete everything prior to location found

	return fullPath;
}

std::string Me::Files::Windows::FileSystem::OpenFile(const char* a_filter, HWND const a_hwnd)
{
	std::string folderPath = Project::ProjectManager::GetAssetBrowserPath();
	std::replace(folderPath.begin(), folderPath.end(), '/', '\\');

	std::string initalDir = FindFullPath();
	initalDir.append(folderPath);

	OPENFILENAMEA ofn;
	CHAR szFile[256] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = a_hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = a_filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = initalDir.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}

	return std::string();
}
std::string Me::Files::Windows::FileSystem::SaveFile(const char* a_filter, HWND const a_hwnd)
{
	std::string folderPath = Project::ProjectManager::GetAssetBrowserPath();
	std::replace(folderPath.begin(), folderPath.end(), '/', '\\');

	std::string initalDir = FindFullPath();
	initalDir.append(folderPath);

	OPENFILENAMEA ofn;
	CHAR szFile[256] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = a_hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = a_filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = initalDir.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetSaveFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}

	return std::string();
}

void Me::Files::Windows::FileSystem::GetFilesOfType(BrowseData& a_data, FileType const a_type, bool const a_recursive, std::string const& a_path)
{
	std::string basePath = a_path;
	if (basePath.empty())
	{
		basePath = Project::ProjectManager::GetAssetBrowserPath();
		if (basePath.empty())
		{
			return;
		}
	}

	a_data.m_path = basePath;

	for(auto& p : std::filesystem::directory_iterator(basePath))
	{
		std::string extention = GetFileExtention(p.path().string());
		std::string path = "";
		Resources::ResourceType type = Resources::ResourceType::Unknown;
		
		std::string name = GetFileName(p.path().filename().string());
		name.append(" (");
		name.append(extention);
		name.append(")");

		if(extention == "glb" || extention == "gltf")
		{
			if (a_type == Files::FileType::Model)
			{
				path = p.path().string();
			}
			type = Resources::ResourceType::Mesh;
		}
		else if(extention == "png" || extention == "dds")
		{
			if (a_type == Files::FileType::Texture)
			{
				path = p.path().string();
			}
			type = Resources::ResourceType::Texture;
		}
		else if(extention == "glsl" || extention == "hlsl")
		{
			if (a_type == Files::FileType::Shader)
			{
				path = p.path().string();
			}
			type = Resources::ResourceType::Shader;
		}
		else if(extention == "lua")
		{
			if (a_type == Files::FileType::Script)
			{
				path = p.path().string();
			}
			type = Resources::ResourceType::Script;
		}
		else if (extention == "scene")
		{
			if (a_type == Files::FileType::Scene)
			{
				path = p.path().string();
			}
			type = Resources::ResourceType::Scene;
		}
		else if (extention == "prefab")
		{
			if (a_type == Files::FileType::Prefab)
			{
				path = p.path().string();
			}
			type = Resources::ResourceType::Prefab;
		}
		else if (extention == "mec")
		{
			if (a_type == Files::FileType::Project)
			{
				path = p.path().string();
			}
		}
		
		if (a_type == Files::FileType::Any && !extention.empty())
		{
			path = p.path().string();
		}

		if(!path.empty())
		{
			std::replace( path.begin(), path.end(), '\\', '/');

			MeduzaFile* file = new MeduzaFile(path, name, extention, type);
			a_data.m_files.push_back(file);
		}

		std::string s = p.path().filename().string();

		if (s.front() != '!' && p.is_directory())
		{
			a_data.m_folders.push_back(s);
			if (a_recursive)
			{
				GetFilesOfType(a_data, a_type, a_recursive, p.path().string());
			}
		}
	}

	if (a_recursive && a_path == "" &&
		(a_type == Files::FileType::Texture || a_type == Files::FileType::Shader))
	{
		GetFilesOfType(a_data, a_type, a_recursive, "Resources");
	}

}

std::string Me::Files::Windows::FileSystem::GetParentPath(std::string const& a_path)
{
	std::string parentPath = std::filesystem::path(a_path).parent_path().string();
	return parentPath;
}