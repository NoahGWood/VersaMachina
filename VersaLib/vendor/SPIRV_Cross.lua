project "SPIRV_Cross"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")


	files
	{
		"SPIRV_Cross/**.hpp",
		"SPIRV_Cross/**.cpp",
		"SPIRV_Cross/**.h",
		"SPIRV_Cross/**.c",
		"%{wks.location}/VersaLib/vendor/glm/glm/**.hpp",
		"%{wks.location}/VersaLib/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"SPIRV_Cross",
		"SPIRV_Cross/include",
		"%{IncludeDir.glm}"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"