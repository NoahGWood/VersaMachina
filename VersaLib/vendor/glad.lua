project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{wks.location}/VersaLib/vendor/glad/include/glad/glad.h",
		"%{wks.location}/VersaLib/vendor/glad/include/KHR/khrplatform.h",
		"%{wks.location}/VersaLib/vendor/glad/src/glad.c"
	}

	includedirs
	{
		"%{wks.location}/VersaLib/vendor/glad/include"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"