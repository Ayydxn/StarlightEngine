project "Starlight Engine"
    targetname "StarlightEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir(getProjectBinariesDir("Engine"))
    objdir(getProjectIntermediateDir("Engine"))

    pchsource "%{prj.location}/Source/StarlightPCH.cpp"
    pchheader "StarlightPCH.h"

    files
    {
        "%{prj.location}/Source/**.cpp",
        "%{prj.location}/Source/**.h"
    }

    includedirs
    {
        "%{prj.location}/Source",
        "%{prj.location}/Source/Runtime",
        "%{prj.location}/Source/Runtime/Core"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "STARLIGHT_PLATFORM_WIN64",

            "WIN32_LEAN_AND_MEAN"
        }

    filter "system:macosx"
        defines
        {
            "STARLIGHT_PLATFORM_MAC"
        }

    filter "system:linux"
        defines
        {
            "STARLIGHT_PLATFORM_LINUX"
        }

    filter "configurations:Debug"
        defines
        {
            "STARLIGHT_BUILD_DEBUG"
        }

    filter "configurations:Release"
        defines
        {
            "STARLIGHT_BUILD_RELEASE"
        }

    filter "configurations:Distribution"
        defines
        {
            "STARLIGHT_BUILD_DISTRIBUTION"
        }