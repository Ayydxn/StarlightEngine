﻿#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <regex>
#include <set>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Runtime/Core/CoreTypes.h"
#include "Runtime/Core/Logging/Logging.h"
#include "Runtime/Core/Misc/AssertionMacros.h"

#ifdef STARLIGHT_PLATFORM_WIN64
    #include <Windows.h>
    #include <WinUser.h>
#endif
