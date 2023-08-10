project "tinyfiledialogs"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")


	files
	{
		"tinyfiledialogs/tinyfiledialogs.h",
		"tinyfiledialogs/tinyfiledialogs.c"
	}

	includedirs
	{
		"tinyfiledialogs"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"