#pragma once
#include "Core/PlatformDetection.h"
#include <memory>
#include <functional>

#ifdef VM_DEBUG
    #if defined(VM_PLATFORM_WINDOWS)
        #define VM_DEBUG_BREAK() __debug_break()
    #elif defined(VM_PLATFORM_LINUX)
        #include <signal.h>
        #define VM_DEBUG_BREAK() raise(SIGTRAP)
    #else
        #error "Platform does not support VM_DEBUG_BREAK()"
    #endif
    #define VM_ENABLE_ASSERTS
#else
    #define VM_DEBUG_BREAK()
#endif

#define VM_EXPAND_MACRO(x) x
#define VM_STRINGIFY_MACRO(x) #x

// #define VM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define VM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace VersaMachina
{
    template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
} // namespace VersaMachina

#include "Core/Log.h"
#include "Core/Assert.h"