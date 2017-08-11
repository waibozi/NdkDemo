cmake_minimum_required(VERSION 3.4.1)

#支持-std=gnu++11
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -DGLM_FORCE_SIZE_T_LENGTH")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FORCE_RADIANS")

add_library( bspatch
             SHARED
             src/main/cpp/bspatch/bspatch.c)

add_library( compress
             SHARED
             src/main/cpp/imagecompress/compress.cpp)

add_library( libjpeg
             SHARED
             IMPORTED)
set_target_properties( libjpeg
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libjpeg.so )

find_library(log-lib log)
find_library(graphics jnigraphics)

#添加多少个lib就需要写多少个target_link_libraries
target_link_libraries( bspatch
                       ${log-lib}
                       ${graphics})

target_link_libraries( compress
                       libjpeg
                       ${log-lib}
                       ${graphics})
