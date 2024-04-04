-- All Starlight Engine dependencies

IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/Engine/ThirdParty/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/Engine/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Engine/ThirdParty/Glad/include"
IncludeDir["Vulkan"] = "%{wks.location}/Engine/ThirdParty/Vulkan/Include"

LibraryDir = {}
LibraryDir["Vulkan"] = "%{wks.location}/Engine/ThirdParty/Vulkan/Lib"

Library = {}
Library["ShaderC_Debug"]=  "%{LibraryDir.Vulkan}/shaderc_sharedd.lib"
Library["ShaderC_Release"] = "%{LibraryDir.Vulkan}/shaderc_shared.lib"