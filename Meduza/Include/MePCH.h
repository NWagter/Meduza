#pragma once

#define NOMINMAX

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

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

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

#pragma warning(disable:4265)
#include <wrl.h>
#pragma warning(default:4265)

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <d3d12sdklayers.h>
#include <d3dx12.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#endif

#ifdef PLATFORM_LINUX
#include <glad/glad.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#endif

#ifdef PLATFORM_APPLE

#endif

#include "Math/MeduzaMath.h"

#include "Core/Core.h"
#include "Core/MeduzaCore.h"

#include "Utils/MeduzaUtils.h"
#include "Platform/General/Events/Events.h"