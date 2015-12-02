solution "Pastorse_Solution"
configurations { "Debug", "Release" }
-- new luis.
location("_build/")
targetdir("_build/bin")
language "C++"

includedirs { "_include","_dependencies/glfw/include", 
		"_dependencies/glfw/src", 
		"_dependencies/glew/include"
		}
		
defines {"GLEW_STATIC", "GLEW_NO_GLU"}

configuration "Debug"
targetsuffix "_d"
defines {"_DEBUG"}
flags { "Symbols" }
    
configuration "Release"
flags { "Optimize" }
  
project "PastorseEngineProject"
kind "ConsoleApp"
language "C++"
links{ "deps","opengl32" }
includedirs { "_include/**.h","_src/**.cc"}
--location "_engine"
--libdirs{"_lib"}
--targetdir "_lib"
files {"_src/*.cc" } -- I quit one * to catch only the root .cc
files { "_include/**.h", "src/**.c" }

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
 


