#pragma once

#define NOMINMAX

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

#include <cassert>
#include <string>
#include <sstream>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <chrono>

#include <glm/glm.hpp>

#ifdef VULKAN_USE
#include <vulkan/vulkan.h>
#endif

#ifdef PLATFORM_WINDOWS

#include <fstream>

#define WINDOWS

//includes for rendering
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ImGui/imgui.h>

#include <ImGui/imgui_impl_win32.h>

#pragma warning(disable:4265)
#include <wrl.h>
#pragma warning(default:4265)

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <d3d12sdklayers.h>
#include <d3dx12.h>

#include <ImGui/imgui_impl_dx12.h>

#include <ImGui/imgui_impl_opengl3.h>

#endif // PLATFORM_WINDOWS

#ifdef PLATFORM_LINUX

#define LINUX 1


#endif
