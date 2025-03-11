project "glew"
   kind "StaticLib"
   language "C"
   staticruntime "off"

   targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
   objdir ("%{wks.location}/Binaries/Intermediates/" .. outputdir .. "/%{prj.name}")

   files
   {
      "include/GL/**.h",
      "src/glew.c",
   }

   includedirs
   {
      "include"
   }

   defines
   {
      "GLEW_STATIC",      -- To match the Makefile static build
      "GLEW_NO_GLU",       -- Exclude GLU support
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