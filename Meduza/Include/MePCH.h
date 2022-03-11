#pragma once

#define NOMINMAX

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <random>

#include <cassert>
#include <string>
#include <cstring>
#include <sstream>
#include <ostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <chrono>
#include <bitset>
#include <fstream>
#include <filesystem>

#include <cereal/archives/xml.hpp>
#include <FontAwesome/FontAwesome.h>

#ifdef PLATFORM_WINDOWS

#include <Windows.h>
#include <wingdi.h>
#include <imgui.h>
#include <ImGuizmo.h>
#include <imgui_internal.h>

#pragma warning(disable:4265)
#include <wrl.h>
#pragma warning(default:4265)

#include <glad/glad.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <d3d12sdklayers.h>
#include <d3dx12.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#define DEBUG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#endif


#ifdef PLATFORM_LINUX

#include <glad/glad.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include <imgui.h>
#include <imgui_internal.h>

#endif

#ifdef PLATFORM_APPLE

#endif

#include "Math/MeduzaMath.h"
#include "Math/GJKAlgorithm.h"

#include "Core/Core.h"
#include "Core/MeduzaCore.h"
#include "Core/MeduzaProfiler.h"

#include "Utils/MeduzaUtils.h"
#include "Platform/General/Events/Events.h"


extern "C" {
      #include <lua.h>
      #include <lualib.h>
      #include <lauxlib.h>
}