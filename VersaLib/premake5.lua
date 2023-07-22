project "VersaLib"
        location "VersaLib"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"
    
        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
        
        pchheader "pch.h"
        pchsource "VersaLib/src/pch.cpp"


	    defines
	    {
	    	"_CRT_SECURE_NO_WARNINGS",
	    	"GLFW_INCLUDE_NONE"
	    }

        files
        {
            "src/**.h",
            "src/**.cpp",
            "platforms/**.h",
            "platforms/**.cpp"
        }
    
        includedirs
        {
            "include",
            "platforms",
            "vendor/spdlog/include"       
        }

    	-- We need GLFW, so we include it
    	includeGLFW()

        links
        {
            "Glad",
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
    