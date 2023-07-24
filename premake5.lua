workspace "VersaMachina"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- This function includes GLFW's header files
function includeGLFW()
    includedirs "VersaLib/vendor/glfw/include"
end

-- This function links statically against GLFW
function linkGLFW()
	libdirs "Libraries/GLFW/Lib"

	-- Our static lib should not link against GLFW
	filter "kind:not StaticLib"
		links "glfw"
	filter {}
end

group "Dependencies"
    include "depends"
    -- include "VersaLib/vendor/glfw"
    include "VersaLib/vendor/glad"
    include "VersaLib/vendor/imgui"

group ""

include "VersaLib"
include "VersaEditor"