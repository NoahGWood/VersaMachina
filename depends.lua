IncludeDir = {}

IncludeDir["GLFW"] = "%{wks.location}/VersaLib/vendor/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/VersaLib/vendor/glad/include"
IncludeDir["ImGUI"] = "%{wks.location}/VersaLib/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/VersaLib/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/VersaLib/vendor/stb_image"
IncludeDir["EnTT"] = "%{wks.location}/VersaLib/vendor/EnTT/include"
IncludeDir["yaml"] = "%{wks.location}/VersaLib/vendor/yaml-cpp/include"
IncludeDir["tinyfiledialogs"] = "%{wks.location}/VersaLib/vendor/tinyfiledialogs"
IncludeDir["ImGuizmo"] = "%{wks.location}/VersaLib/vendor/ImGuizmo"
IncludeDir["shaderc"] = "%{wks.location}/VersaLib/vendor/shaderc/libshaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/VersaLib/vendor/SPIRV_Cross"
IncludeDir["Vulkan"] = "%{wks.location}/VersaLib/vendor/Vulkan"
--IncludeDir["mono"] = "%{wks.location}/VersaLib/vendor/mono"

LibraryDir = {}
--LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
--LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/Hazel/vendor/VulkanSDK/Lib"
--LibraryDir["mono"] = "%{wks.location}/VersaLib/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
--Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
--Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

--Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
--Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
--Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
--Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

--Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
--Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
--Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

--Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"