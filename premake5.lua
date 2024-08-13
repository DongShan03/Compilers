workspace "Compilers"
    configurations { "Debug", "Release" }
    platforms { "Win64" }
    language "C++"
    location "build"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"

project("Compilers")
    kind("ConsoleApp")
    targetdir "build/%{cfg.buildcfg}"
    files { "/headers/**.*", "main.cpp" }
