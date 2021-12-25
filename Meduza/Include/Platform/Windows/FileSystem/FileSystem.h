#pragma once

#include "Platform/General/FileSystem/FileSystem.h"

namespace Me
{
    namespace Files
    {
		enum class FileType : int
		{
			Model,
            Prefab,
			Texture,
			Shader,
			Scene,
            Script,

            Any
		};

        namespace Windows
        {
            class FileSystem : public Files::FileSystem
            {
                public:
                    static std::string OpenFile(const char* a_filter, HWND const a_hwnd);
                    static std::string SaveFile(const char* a_filter, HWND const a_hwnd);
                    static void GetFilesOfType(BrowseData& a_data, FileType const a_type, bool const a_recursive = true, std::string const& a_path = "Assets");
                    static std::string GetParentPath(std::string const& a_path);
            };
        }
    }
}