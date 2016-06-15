solution "Pastorse_Solution"
configurations { "Debug", "Release" }
location("_build/")
targetdir("_build/bin")
language "C++"

includedirs { 	"_include",
		"_dependencies/glfw/include", 
		"_dependencies/glfw/src", 
		"_dependencies/glew/include",
		"_dependencies/glm/glm",
		"_dependencies/stb_image/include_src",
		"_dependencies/tinyobjloader/",
		"_dependencies/lua-bridge/LuaBridge",
		"_dependencies/lua-bridge/LuaBridge/detail",
		"_dependencies/lua/"
	    }
		
defines {"GLEW_STATIC", "GLEW_NO_GLU"}

configuration "Debug"
    targetsuffix "_d"
    defines {"_DEBUG"}
    flags { "Symbols" }
    
configuration "Release"
flags { "Optimize" }


project "_examples_Shadows"
kind "ConsoleApp"
files{"_examples/_Shadows/**.cc"}
links{ "opengl32","deps", "platform_Win32", "PastorseEngineProject"}

project "_demo"
kind "ConsoleApp"
files{"_examples/_demo/**.cc"}
links{ "opengl32","deps", "platform_Win32", "PastorseEngineProject"}
  
project "PastorseEngineProject"
kind "StaticLib"
language "C++"
includedirs { "_include/**.h","_src/**.cc"}
files {"_src/*.cc" }
files { "_include/**.h", "src/**.c" }

project "platform_Win32"
kind "StaticLib"
files {"_src/_platforms/_Win32/**.cc"}

project "deps"
kind "StaticLib"
files { "_dependencies/glfw/src/*.c", "_dependencies/glfw/include/*.h"}
 excludes{"_dependencies/glfw/src/egl_context.c",
               "_dependencies/glfw/src/glx_context.c",
               "_dependencies/glfw/src/linux_joystick.c",
               "_dependencies/glfw/src/mach_time.c",
               "_dependencies/glfw/src/mir_init.c",
               "_dependencies/glfw/src/mir_monitor.c",
               "_dependencies/glfw/src/mir_window.c",
               "_dependencies/glfw/src/posix_time.c",
               "_dependencies/glfw/src/posix_tls.c",
               "_dependencies/glfw/src/xkb_unicode.c",
               "_dependencies/glfw/src/x11_window.c",
               "_dependencies/glfw/src/x11_monitor.c",
               "_dependencies/glfw/src/x11_init.c",
               "_dependencies/glfw/src/wl_init.c",
               "_dependencies/glfw/src/wl_monitor.c",
               "_dependencies/glfw/src/wl_window.c"
            }
defines {"_GLFW_WIN32", "_GLFW_USE_OPENGL", "_GLFW_WGL", "_GLFW_BUILD_DLL"}
files {"_dependencies/glew/src/glew.c"} 
files {"_dependencies/glm/glm/**.inl"}
files {"_dependencies/stb_image/include_src/**.c"}
files {"_dependencies/tinyobjloader/**.cc"}
files {"_dependencies/lua/**.c"}
 


