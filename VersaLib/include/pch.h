#include <Core/Base.h>
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

#include "Profiler/Profiler.h"

#ifndef BIT
    #define BIT(x) (1<<x)
#endif 

#ifdef VM_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
