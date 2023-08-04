IncludeDir = {}

IncludeDir["GLFW"] = "%{wks.location}/VersaLib/vendor/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/VersaLib/vendor/glad/include"
IncludeDir["ImGUI"] = "%{wks.location}/VersaLib/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/VersaLib/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/VersaLib/vendor/stb_image"
IncludeDir["EnTT"] = "%{wks.location}/VersaLib/vendor/EnTT/include"
--IncludeDir["mono"] = "%{wks.location}/VersaLib/vendor/mono"

LibraryDir = {}

--LibraryDir["mono"] = "%{wks.location}/VersaLib/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}

--Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"