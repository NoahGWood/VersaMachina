#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>


#include "Core/Base.h"

#include "Core/Log.h"

//#include "Hazel/Debug/Instrumentor.h"

#ifndef BIT
    #define BIT(x) (1<<x)
#endif 

#ifdef VM_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#ifdef VM_PLATFORM_LINUX

#endif

#define VM_PROFILE_FUNCTION()