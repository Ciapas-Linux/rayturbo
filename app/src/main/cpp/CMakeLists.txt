
cmake_minimum_required(VERSION 3.4.1)

project("rayturbo")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/include )
include_directories(src/main/cpp/)
include_directories(${ANDROID_NDK}/sources/android/native_app_glue)

add_library(libraylib STATIC IMPORTED)
set_target_properties(libraylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libraylib.a)

add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

if(${ANDROID_ABI} STREQUAL "x86_64")

endif()




add_library(rayturbo
            SHARED
            main.cpp
            Game.cpp Game.h
            Button.cpp Button.h
            BitmapFont.cpp BitmapFont.h)


find_library( log-lib
              log )

target_link_libraries( rayturbo
                       android
                       native_app_glue
                       EGL
                       GLESv2
                       atomic
                       c
                       m
                       dl
                       OpenSLES
                       libraylib
                       ${log-lib}
                     )
