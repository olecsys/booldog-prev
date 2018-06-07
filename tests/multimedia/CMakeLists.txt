cmake_minimum_required (VERSION 2.8)
project (multimedia)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)    
    set(IVCONAN_USING TRUE)
elseif(EXISTS "${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake")
    include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)    
    set(IVCONAN_USING TRUE)
elseif(EXISTS "${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake")
    include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)    
    set(IVCONAN_USING TRUE)    
endif()
if(DEFINED IVCONAN_USING)
    conan_basic_setup()
endif()

get_filename_component(IVBUILD_DIR "${CMAKE_BINARY_DIR}/../${IVOUTPUT_RELATIVE_DIRECTORY}" ABSOLUTE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${IVBUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${IVBUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${IVBUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

file(GLOB_RECURSE sources main.cpp)

if(MSVC)
    file(GLOB_RECURSE resources ./*.rc)
    # set(DEPS_LIBS "${CMAKE_SOURCE_DIR}/libs/librux.framework.lib")

    set(CMAKE_CXX_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS "")

# компилятор(общие)
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi") # формат отладочной информации

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4") # уровень предупреждений

    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # обрабатывать предупреждения как ошибки

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP") # многопроцессорная компиляция

# компилятор(оптимизация)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Od") # оптимизация

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Os") # предпочитать размер или скорость

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Oy-") # опустить указатели на фреймы

    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GL") # оптимизация всей программы

# компилятор(создание кода)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF-") # включить объединение строк

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gm-") # включить минимальное перестроение

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc") # включить C++ исключения

    if(DEFINED IVCONAN_USING)
        message("conan.io is using")
    else()
        #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD") # библиотека времени выполнения
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GS") # проверка переполнения буфера

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gy") # включить компоновку на уровне функций

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise") # модель вычислений с плавающей точкой

# компилятор(язык)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t") # считать wchar_t встроенным типом

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:forScope") # обеспечение согласованности видимости переменных, объявленных в заголовке оператора for
# компилятор(дополнительно)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gd") # соглашение о вызовах

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4714") # отключить некоторые предупреждения

# компоновщик(общие)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO") # включить инкрементную компоновку
# компоновщик(отладка)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG") # включить инкрементную компоновку
# компоновщик(оптимизация)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:NOREF") # ссылки

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:NOICF") # включить свертывание записей COMDAT
else()
    set(DEPS_LIBS "rt"
                  "dl"
                  "pthread"
                  "avformat"
                  "avcodec"
                  "avutil"
                  "swscale"
                  "turbojpeg")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fvisibility=hidden -rdynamic -ffunction-sections -fdata-sections -gdwarf-2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIC -Wl,-E,--no-undefined,-O0,-flto,--gc-sections,-R,'$$ORIGIN/lib',-R,'$ORIGIN/lib',--build-id=sha1")
endif()

add_executable(${PROJECT_NAME} ${sources} ${resources})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PUBLIC ${DEPS_LIBS})