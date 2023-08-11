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
-- Leave commented to build with system GLFW
-- Uncomment to build with git submodule glfw (build errors, glfw.lua needs fixed)
--    include "VersaLib/vendor/glfw"
    include "VersaLib/vendor/glad"
    include "VersaLib/vendor/imgui"
    include "VersaLib/vendor/yaml"
    include "VersaLib/vendor/tinyfiledialogs"
    include "VersaLib/vendor/ImGuizmo"

group ""

include "VersaLib"
include "VersaEditor"