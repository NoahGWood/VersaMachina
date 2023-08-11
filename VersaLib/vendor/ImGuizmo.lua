project "ImGuizmo"
    kind "StaticLib"
    language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")

    files
	{
		"ImGuizmo/*.h",
		"ImGuizmo/*.cpp",
	}

	includedirs
	{
        "%{IncludeDir.ImGUI}",
		"ImGuizmo"
	}
	links {
		"ImGUI"
	}
	flags { "NoPCH" }
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"