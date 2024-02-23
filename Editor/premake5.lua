project "Starlight Editor"
    targetname "StarlightEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir(getProjectBinariesDir("Editor"))
    objdir(getProjectIntermediateDir("Editor"))

    files
    {
        "%{prj.location}/Source/**.cpp",
        "%{prj.location}/Source/**.h"
    }

    includedirs
    {
        "%{prj.location}/Source",

        "%{wks.location}/Engine/Source",
        "%{wks.location}/Engine/Source/Runtime",
        "%{wks.location}/Engine/Source/Runtime/Core"
    }

    links
    {
        "Starlight Engine"
    }

    filter "system:windows"
        systemversion "latest"
        entrypoint "WinMainCRTStartup"

        defines
        {
            "STARLIGHT_PLATFORM_WIN64"
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
        kind "WindowedApp"

        defines
        {
            "STARLIGHT_BUILD_DISTRIBUTION"
        }