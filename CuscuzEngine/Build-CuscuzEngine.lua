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
   }

   includedirs
   {
      "Source",
      "Dependencies/SDL2/include",
      "Dependencies/SDL2_image/include",
      
      "%{includedir.ImGui}",
      "%{includedir.SPD_Log}",
      "%{includedir.glm}",
      "%{includedir.yaml}"
   }

   libdirs
   { 
      "Dependencies/SDL2/lib",
      "Dependencies/SDL2_image/lib" 
   } 

   links
   {
      "ImGui",
      "yaml-cpp",
      "SDL2.lib",
      "SDL2main.lib",
      "SDL2_image.lib",
   }

   targetdir ("../Binaries/" .. outputdir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
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