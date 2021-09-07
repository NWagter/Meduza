#pragma once

#include "Platform/General/FileSystem/FileSystem.h"

namespace Me
{
    namespace Files
    {
        namespace Windows
        {
            class FileSystem : public Files::FileSystem
            {
                public:
                    static std::string OpenFile(const char* a_filter, HWND a_hwnd);
                    static std::string SaveFile(const char* a_filter, HWND a_hwnd);
            };
        }
    }
}