local module_name = "test"

workspace (module_name)
    configurations { "Win64", "Win32", "Unix64", "Elbrus64"}

project (module_name)
    language "C++"
    kind "ConsoleApp"
    defines { "NDEBUG" }    
    symbols "On"
    files {
        "src/*.cpp"
    }
    includedirs {
        "src"
    }

    filter "configurations:Win32 or Win64"
        system "windows"

    filter "configurations:Win32"
        architecture "x86"
    
    filter "configurations:Win64 or Unix64 or Elbrus64"
        architecture "x86_64"

    filter "configurations:Unix64 or Elbrus64"
        system "linux"
        buildoptions {
            "-std=gnu++0x",
            "-fvisibility=hidden",
            --"-fPIC",
	    "-rdynamic",
            "-ffunction-sections",
            "-fdata-sections"
        }
        links {
           "pthread",
           "dl",
           "rt"
        }
    
    filter "configurations:Unix64"
        buildoptions {
            --"-m64"
        }
        linkoptions {
            "-fPIC -m64 -Wl,-E,--no-undefined,-O2,-flto,--gc-sections,-R,'$$ORIGIN/lib',--build-id=sha1"
        }
        local build_dir = "build/x64"
        targetdir (build_dir)

    filter "configurations:Elbrus64"
        require "elbrus"
        
        toolset "elbrus"

        includedirs {
            "/opt/mcst/crossfs-current.e2k-4c.3.14/usr/include"
        }            
        buildoptions {
            --"-m64"
        }
        linkoptions {
            --"-shared -fPIC -m64 -Wl,-E,--no-undefined,-O2,-flto,--gc-sections,--strip-all,-R,'$$ORIGIN/lib',--build-id=sha1"
            "-fPIC -mptr64 -Wl,-E,--no-undefined,-O2,-flto,--gc-sections,-R,'$$ORIGIN/lib',--build-id=sha1"
        }
        libdirs {
            "/opt/mcst/crossfs-current.e2k-4c.3.14/usr/lib"
        }
        local build_dir = "build/elbrus"
        targetdir (build_dir)