project "CuscuzEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   pchheader "pch.h"
   pchsource "Source/pch.cpp"

   files 
   {
      "Source/**.h",
      "Source/**.cpp",
      "%{includedir.glm}/**.hpp",
      "%{includedir.glm}/**.inl",
      "%{includedir.stb_image}/**.h",
		"%{includedir.stb_image}/**.cpp",
   }

   includedirs
   {
      "Source",

      "%{includedir.SDL2}",
      "%{includedir.glm}",
      "%{includedir.SPD_Log}",
      "%{includedir.ImGui}",
      "%{includedir.yaml}",
      "%{includedir.glew}",
      "%{includedir.stb_image}",
   }

   libdirs
   { 
      "Dependencies/SDL2/lib",
   } 

   links
   {
      "ImGui",
      "yaml-cpp",
      "glew",
      "SDL2.lib",
      "SDL2main.lib",
      "opengl32.lib",
   }

   defines
   {
        "GLEW_STATIC",      -- To match the Makefile static build
        "GLEW_NO_GLU",       -- Exclude GLU support
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
        "_CRT_SECURE_NO_WARNINGS",
   }

   linkoptions { "/IGNORE:4006" }

   targetdir ("../Binaries/" .. outputdir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG", "CC_ENABLE_ASSERT", "CC_PROFILE" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"