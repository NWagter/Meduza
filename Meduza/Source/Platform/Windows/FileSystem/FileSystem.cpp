#include "MePCH.h"
#include "Platform/Windows/FileSystem/FileSystem.h"

#include <filesystem>

std::string Me::Files::Windows::FileSystem::OpenFile(const char* a_filter, HWND a_hwnd)
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
std::string Me::Files::Windows::FileSystem::SaveFile(const char* a_filter, HWND a_hwnd)
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

void Me::Files::Windows::FileSystem::GetFilesOfType(BrowseData& a_data, FileType a_type, std::string a_path)
{
	a_data.m_path = a_path;

	for(auto& p : std::filesystem::directory_iterator(a_path))
	{
		std::string extention = GetFileExtention(p.path().string());
		std::string path = "";
		
		std::string name = GetFileName(p.path().filename().string());
		name.append(" (");
		name.append(extention);
		name.append(")");

		if(a_type == Files::FileType::Model && (extention == "glb" || extention == "gltf"))
		{
			path = p.path().string();
		}
		if(a_type == Files::FileType::Texture && (extention == "png" || extention == "dds"))
		{
			path = p.path().string();
		}
		if(a_type == Files::FileType::Shader && (extention == "glsl" || extention == "hlsl"))
		{
			path = p.path().string();
		}
		if(a_type == Files::FileType::Script && (extention == "lua"))
		{
			path = p.path().string();
		}

		if(!path.empty())
		{
			std::replace( path.begin(), path.end(), '\\', '/');
			a_data.m_files.push_back(std::pair<std::string, std::string>(name, path));
		}

		if(p.is_directory())
		{
			GetFilesOfType(a_data, a_type, p.path().string());
		}
	}
}