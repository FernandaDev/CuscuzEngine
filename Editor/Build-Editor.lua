project "Editor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files
   {
        "Source/**.h",
        "Source/**.cpp",
        "Assets/**.glsl",
        "Assets/**.png",
        "Assets/**.bmp",
        "Assets/**.jpeg",
   }

   includedirs
   {
        "Source",
        "Assets",

        "%{wks.location}/CuscuzEngine/Source",
        "%{wks.location}/CuscuzEngine/Vendor",

        "%{includedir.SPD_Log}",
        "%{includedir.SDL2}",
        "%{includedir.glm}",
   }

   -- libdirs {} 

   links
   {
      "CuscuzEngine",
   }

   postbuildcommands
   {
      '{COPYDIR} "' .. engine_dlls .. '" "$(TargetDir)"'
   }

   targetdir ("../Binaries/" .. outputdir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       --linkoptions { "/WHOLEARCHIVE:CuscuzEngine.lib", "/ENTRY:mainCRTStartup"}

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