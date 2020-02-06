#pragma once

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
#include "Helper/Dx12_Helper.h"

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif