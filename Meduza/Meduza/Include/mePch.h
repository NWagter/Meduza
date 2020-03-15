#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

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

#ifdef PLATFORM_WINDOWS

//includes for rendering
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <d3d12sdklayers.h>

#endif // PLATFORM_WINDOWS

