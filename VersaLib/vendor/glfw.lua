project "GLFW"
	kind "StaticLib"
	language "C"
	warnings "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")


	files
	{
		"glfw/include/GLFW/glfw3.h",
		"glfw/include/GLFW/glfw3native.h",
		"glfw/src/internal.h",
		"glfw/src/platform.h",
		"glfw/src/mappings.h",
		"glfw/src/context.c",
		"glfw/src/init.c",
		"glfw/src/input.c",
		"glfw/src/monitor.c",
		"glfw/src/platform.c",
		"glfw/src/vulkan.c",
		"glfw/src/window.c",
		"glfw/src/egl_context.c",
		"glfw/src/osmesa_context.c",
		"glfw/src/null_platform.h",
		"glfw/src/null_joystick.h",
		"glfw/src/null_init.c",
		"glfw/src/null_monitor.c",
		"glfw/src/null_window.c",
		"glfw/src/null_joystick.c",		
	
	}

	includedirs
	{
		"glfw/include"
	}
	filter "system:linux"
		pic "On"
		staticruntime "On"
		systemversion "latest"

		files
		{
			"glfw/include/posix_time.h",
			"glfw/deps/tinycthread.h",
			"glfw/include/posix_thread.h",

			"glfw/src/posix_module.c",
			"glfw/src/posix_time.c",
			"glfw/deps/tinycthread.c",
			"glfw/src/posix_thread.c",

			"glfw/include/x11_platform.h",
			"glfw/include/xb_unicode.h",
			"glfw/src/x11_init.c",
			"glfw/src/wl_init.c",
			"glfw/src/wl_monitor.c",
			"glfw/src/wl_window.c",
			"glfw/src/x11_window.c",
			"glfw/src/xkb_unicode.c",


			"glfw/include/linux_joystick.h",
			"glfw/src/linux_joystick.c",

			"glfw/include/posix_poll.h",
			"glfw/src/posix_poll.c",
		}

		defines
		{
			"_GLFW_X11"
		}
	
		buildoptions
		{
			"-pthread"
		}

		links 
		{
			"X11",
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"glfw/src/win32_init.c",
			"glfw/src/win32_joystick.c",
			"glfw/src/win32_monitor.c",
			"glfw/src/win32_time.c",
			"glfw/src/win32_thread.c",
			"glfw/src/win32_window.c",
			"glfw/src/wgl_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"