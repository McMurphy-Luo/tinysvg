cmake_minimum_required(VERSION 3.5)
project(easy-svg C CXX)
set(CMAKE_CXX_STANDARD 11)

if(${UNIX})
    set(CMAKE_CXX_FLAGS "-Werror -Wall -O0 -g")
endif(${UNIX})

set(output_dir ${PROJECT_SOURCE_DIR}/build)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${output_dir})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${output_dir})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${output_dir})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${output_dir})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${output_dir})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${output_dir})

set(source_dir ${PROJECT_SOURCE_DIR}/src)
set(test_source_dir ${PROJECT_SOURCE_DIR}/test)

include_directories(${source_dir})
list(APPEND source
        ${source_dir}/common/Global.h
        ${source_dir}/common/Point.cpp
        ${source_dir}/common/Point.h
        ${source_dir}/common/Size.cpp
        ${source_dir}/common/Size.h
        ${source_dir}/common/Utf8String.cpp
        ${source_dir}/common/Utf8String.h

        ${source_dir}/svg/Rectangle.cpp
        ${source_dir}/svg/Rectangle.h
        ${source_dir}/svg/Circle.cpp
        ${source_dir}/svg/Circle.h
        ${source_dir}/svg/Color.cpp
        ${source_dir}/svg/Color.h
        ${source_dir}/svg/Line.cpp
        ${source_dir}/svg/Line.h
        )

list(APPEND test_source
        ${test_source_dir}/main.cpp)
add_executable(test ${test_source})
add_library(EasySvg ${source})

target_compile_definitions(EasySvg PUBLIC "MUI")

if(${WIN32})
    target_compile_definitions(EasySvg PUBLIC "UNICODE" "_UNICODE")
    target_compile_definitions(test PUBLIC "UNICODE" "_UNICODE")
    target_link_libraries(EasySvg d2d1.lib dwrite.lib ComCtl32.lib)
    set_target_properties(test PROPERTIES WIN32_EXECUTABLE TRUE)
endif(${WIN32})

set_target_properties(EasySvg PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${output_dir})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
