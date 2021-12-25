#include "MePCH.h"
#include "Platform/Windows/FileSystem/FileSystem.h"

#include <filesystem>
#include "Platform/General/Resources/Resource.h"

std::string Me::Files::Windows::FileSystem::OpenFile(const char* a_filter, HWND const a_hwnd)
{
	char path[260];
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, path, (sizeof(path)));
	OPENFILENAMEA ofn;
	CHAR szFile[260] = {0};

	std::string initalDir = path;

	size_t pos = initalDir.find("Sandbox.exe"); //find location of word
    initalDir.erase(pos,initalDir.size() - pos); //delete everything prior to location found
	initalDir.append("Assets");

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
	char path[260];
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, path, (sizeof(path)));
	OPENFILENAMEA ofn;
	CHAR szFile[260] = {0};

	std::string initalDir = path;

	size_t pos = initalDir.find("Sandbox.exe"); //find location of word
    initalDir.erase(pos,initalDir.size() - pos); //delete everything prior to location found
	initalDir.append("Assets");
	
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
	a_data.m_path = a_path;

	for(auto& p : std::filesystem::directory_iterator(a_path))
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
		
		if (a_type == Files::FileType::Any && !extention.empty())
		{
			path = p.path().string();
		}

		if(!path.empty())
		{
			std::replace( path.begin(), path.end(), '\\', '/');

			MeduzaFile file(path, name, extention, type);
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

	if (a_recursive && a_path == "Assets" &&
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