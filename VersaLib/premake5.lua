project "VersaLib"
        location "VersaLib"
        kind "StaticLib"
        language "C++"
        cppdialect "C++2a"
        staticruntime "off"
        systemversion "latest"
    
        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
        
        pchheader "pch.h"
        pchsource "VersaLib/src/pch.cpp"


	    defines
	    {
	    	"_CRT_SECURE_NO_WARNINGS",
	    	--"GLFW_INCLUDE_NONE"
	    }

        files
        {
            "%{wks.location}/VersaLib/src/**.h",
            "%{wks.location}/VersaLib/src/**.cpp",
            "%{wks.location}/VersaLib/platforms/**.h",
            "%{wks.location}/VersaLib/platforms/**.cpp",
            "%{wks.location}/VersaLib/vendor/glm/glm/**.hpp",
            "%{wks.location}/VersaLib/vendor/glm/glm/**.inl",
            "%{wks.location}/VersaLib/vendor/stb_image/**.h",
            "%{wks.location}/VersaLib/vendor/stb_image/**.cpp",
            
        }
    
        includedirs
        {
            "include",
            "platforms",
            "vendor/spdlog/include",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.ImGUI}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.stb_image}",
            "%{IncludeDir.EnTT}",
            "%{IncludeDir.yaml}",
            "%{IncludeDir.tinyfiledialogs}"

        }

    	-- We need GLFW, so we include it
    	--includeGLFW()

        links
        {
            "glfw",
            "Glad",
            "ImGui",
            "yaml",
            "tinyfiledialogs"
        }
        flags { "NoPCH" }
        filter "system:windows"
    
            defines
            {
                "VM_PLATFORM_WINDOWS",
                "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
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
    
