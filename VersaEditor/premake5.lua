    
project "VersaEditor"
location "VersaEditor"
kind "ConsoleApp"
language "C++"
cppdialect "C++2a"
staticruntime "off"
systemversion "latest"

targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")

files
{
    "src/core/**.h",
    "src/core/**.cpp",
    "src/**.h",
    "src/**.cpp"
}


includedirs
{
    "include",
    "%{wks.location}/VersaLib/include",
    "%{wks.location}/VersaLib/platforms",
    "%{wks.location}/VersaLib/vendor",
    "%{wks.location}/VersaLib/vendor/spdlog/include",
    "%{IncludeDir.glm}",
	"%{IncludeDir.EnTT}"
}

links
{
    "VersaLib"
}

filter "system:windows"

    defines
    {
        "VM_PLATFORM_WINDOWS",
        "VM_BUILD_DLL"
    }
    links
    {
        "glfw",
        "OpenGL32"
    }

filter "system:linux"
    pic "On"

    defines
    {
        "VM_PLATFORM_LINUX",
        "VM_BUILD_SHARED",
    }
    links
    {
        "glfw",
        "Glad",
        "dl",
        "GL",
        "ImGUI"
    }

filter "configurations:Debug"
    defines {
        "VM_DEBUG", "VM_PROFILE"
    }
    symbols "On"


filter "configurations:Release"
    defines "VM_RELEASE"
    optimize "On"

filter "configurations:Dist"
    defines "VM_DIST"
    optimize "On"
