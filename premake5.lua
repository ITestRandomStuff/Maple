workspace "Maple"
    configurations { "Debug", "Release" }
    architecture "x86_64"

include "Maple/vendor/glfw"
include "Maple/vendor/glad"
include "Maple/vendor/imgui"

project "Maple"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    location "%{prj.name}"

    targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    pchsource "Maple/source/pch.cpp"
    pchheader "pch.h"

    files {
        "%{prj.name}/source/**.h", "%{prj.name}/source/**.cpp",
    }

    includedirs {
        "%{prj.name}/source",

        "%{prj.name}/vendor/glfw/include",
        "%{prj.name}/vendor/glad/include",

        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/imgui",
        "%{prj.name}/vendor/stb_image"
    }

    links {
        "opengl32.lib",
        "GLFW",
        "GLAD",

        "ImGui"
    }

    defines {
        "_USE_MATH_DEFINES",
        "IMGUI_IMPL_OPENGL_CUSTOM_LOADER"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "MPL_SYSTEM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines { "MPL_CONFIG_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "MPL_CONFIG_RELEASE" }
        optimize "on"