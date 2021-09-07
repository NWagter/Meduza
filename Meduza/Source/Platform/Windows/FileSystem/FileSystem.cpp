#include "MePCH.h"
#include "Platform/Windows/FileSystem/FileSystem.h"

std::string Me::Files::Windows::FileSystem::OpenFile(const char* a_filter, HWND a_hwnd)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = {0};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = a_hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = a_filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}

	return std::string();
}
std::string Me::Files::Windows::FileSystem::SaveFile(const char* a_filter, HWND a_hwnd)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = {0};
	
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = a_hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = a_filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetSaveFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}

	return std::string();
}