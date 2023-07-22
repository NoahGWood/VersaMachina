#pragma once

#include "Core/Base.h"
#include "Core/Log.h"
#include <filesystem>

#ifdef VM_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define VM_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { VM##type##ERROR(msg, __VA_ARGS__); VM_DEBUG_BREAK(); } }
	#define VM_INTERNAL_ASSERT_WITH_MSG(type, check, ...) VM_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define VM_INTERNAL_ASSERT_NO_MSG(type, check) VM_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", VM_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define VM_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define VM_INTERNAL_ASSERT_GET_MACRO(...) VM_EXPAND_MACRO( VM_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, VM_INTERNAL_ASSERT_WITH_MSG, VM_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define VM_ASSERT(...) VM_EXPAND_MACRO( VM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define VM_CORE_ASSERT(...) VM_EXPAND_MACRO( VM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define VM_ASSERT(...)
	#define VM_CORE_ASSERT(...)
#endif