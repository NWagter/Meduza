#pragma once

#include "Platform/General/FileSystem/FileSystem.h"

namespace Me
{
    namespace Files
    {
		enum class FileType : int
		{
			Model,
			Texture,
			Shader,
			Scene,
            Script
		};

        namespace Windows
        {
            class FileSystem : public Files::FileSystem
            {
                public:
                    static std::string OpenFile(const char* a_filter, HWND const a_hwnd);
                    static std::string SaveFile(const char* a_filter, HWND const a_hwnd);
                    static void GetFilesOfType(BrowseData& a_data, FileType const a_type, std::string const& a_path = "Assets");
            };
        }
    }
}