project "shaderc"
	kind "StaticLib"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")


	files
	{
		"shaderc/libshaderc/**.hpp",
		"shaderc/libshaderc/**.cpp",
		"shaderc/libshaderc/**.h",
		"shaderc/libshaderc/**.c",
		"shaderc/libshaderc_util/**.hpp",
		"shaderc/libshaderc_util/**.cpp",
		"shaderc/libshaderc_util/**.h",
		"shaderc/libshaderc_util/**.c",

    }

	includedirs
	{
        "SPIRV_Cross/include",
		"shaderc/libshaderc",
		"shaderc/libshaderc/include",
		"shaderc/libshaderc_util",
		"shaderc/libshaderc_util/include",
        "/home/noah/Desktop/1.3.250.1/source/SPIRV-Headers/include/",
        "/home/noah/Desktop/1.3.250.1/source/SPIRV-Tools/include"
	}

    links
	{
		"SPIRV_Cross",
    }
	
	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"