project "SOIL"
   kind "StaticLib"
   language "C"
   staticruntime "off"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files
   {
      "src/**.h",
      "src/**.c",
   }

   includedirs
   {
      "src"
   }

   defines
   {
      "_CRT_SECURE_NO_WARNINGS",
   }

   filter "system:windows"
      systemversion "latest"

   filter "configurations:Debug"
      runtime "Debug"
      symbols "on"
      defines { "DEBUG" }

   filter "configurations:Release"
      runtime "Release"
      optimize "on"
      defines { "NDEBUG" }
      buildoptions { "-s" }  -- This strips symbols in release builds (like the Makefile strip)

   filter "configurations:Dist"
		runtime "Release"
		optimize "on"
      symbols "off"
      defines { "NDEBUG" }
      buildoptions { "-s" }  -- This strips symbols in release builds (like the Makefile strip)