local module_name = "test"

workspace (module_name)
    configurations { "win64", "win32", "unix64"}

project (module_name)
    language "C++"
    kind "ConsoleApp"
    defines { "NDEBUG" }    
    symbols "On"
    files {
        "*.cpp"
    }
    includedirs {
        "."
    }

    filter "configurations:win32 or win64"
        system "windows"

    filter "configurations:win32"
        architecture "x86"
    
    filter "configurations:win64 or unix64"
        architecture "x86_64"

    filter "configurations:unix64"
        system "linux"
        buildoptions {
            "-std=gnu++0x",
            "-fvisibility=hidden",
	        "-rdynamic",
            "-ffunction-sections",
            "-fdata-sections"
        }
        links {
           "pthread",
           "dl",
           "rt",
           "turbojpeg"
        }
    
    filter "configurations:unix64"
        buildoptions {
        }
        linkoptions {
            "-fPIC -m64 -Wl,-E,--no-undefined,-O2,-flto,--gc-sections,-R,'$$ORIGIN/lib',--build-id=sha1"
        }
    filter{}
        local build_dir = "build"
        targetdir (build_dir .. "/%{cfg.architecture}")