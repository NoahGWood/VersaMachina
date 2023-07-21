workspace "VersaMachina"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "VersaLib"
        location "VersaLib"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"
    
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("build/" .. outputdir .. "/%{prj.name}")
        
        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
    
        includedirs
        {
            "%{prj.name}/include"
        }
   
        filter "system:windows"
    
            defines
            {
                "VM_PLATFORM_WINDOWS"
            }
    
        filter "system:linux"
            defines
            {
                "VM_PLATFORM_LINUX"
            }
    
        filter "configurations:Debug"
            defines "VM_DEBUG"
            symbols "On"
    
    
        filter "configurations:Release"
            defines "VM_RELEASE"
            optimize "On"
    
        filter "configurations:Dist"
            defines "VM_DIST"
            optimize "On"
    
    
project "VersaEditor"
    location "VersaEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/include",
        "%{wks.location}/VersaLib/include"
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

    filter "system:linux"
        pic "On"

        defines
        {
            "VM_PLATFORM_LINUX",
            "VM_BUILD_SHARED"
        }

    filter "configurations:Debug"
        defines "VM_DEBUG"
        symbols "On"


    filter "configurations:Release"
        defines "VM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "VM_DIST"
        optimize "On"
