#pragma once

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")


#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <d3d12sdklayers.h>

//DirectX 12 Extention
#pragma warning(push, 0)//disables most external warnings except for ones below
#pragma warning(disable: 26495)
#pragma warning(disable: 26451)
#pragma warning(disable: 26812)
#pragma warning (pop)
#include <d3dx12.h>

// Others
#include <Windows.h>

#include <wrl.h>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>

#include <codecvt>
#include <locale>
#include <chrono>
#include "imgui.h"

#include "Helper/Helper.h"

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

static const int gs_frameBufferCount = 3;

inline void ThrowIfFailed(HRESULT a_Hr)
{
	if (FAILED(a_Hr))
	{
		throw std::exception();
	}
}