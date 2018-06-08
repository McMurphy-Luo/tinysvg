cmake_minimum_required(VERSION 3.5)
project(tinysvg C CXX)
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

list(APPEND source ${source_dir}/Config.h)
list(APPEND source ${source_dir}/parser/SVGDocumentParser.cpp
                   ${source_dir}/parser/SVGDocumentParser.h
                    )
list(APPEND source
        ${source_dir}/Config.h
        ${source_dir}/svg/DOMString.cpp
        ${source_dir}/svg/DOMString.h
        ${source_dir}/svg/SVGBase.cpp
        ${source_dir}/svg/SVGBase.h
        ${source_dir}/svg/SVGCircle.cpp
        ${source_dir}/svg/SVGCircle.h
        ${source_dir}/svg/SVGColor.cpp
        ${source_dir}/svg/SVGColor.h
        ${source_dir}/svg/SVGEllipse.cpp
        ${source_dir}/svg/SVGEllipse.h
        ${source_dir}/svg/SVGLength.cpp
        ${source_dir}/svg/SVGLength.h
        ${source_dir}/svg/SVGLine.cpp
        ${source_dir}/svg/SVGLine.h
        ${source_dir}/svg/SVGPoint.cpp
        ${source_dir}/svg/SVGPoint.h
        ${source_dir}/svg/SVGPolygon.cpp
        ${source_dir}/svg/SVGPolygon.h
        ${source_dir}/svg/SVGPolyline.cpp
        ${source_dir}/svg/SVGPolyline.h
        ${source_dir}/svg/SVGRect.cpp
        ${source_dir}/svg/SVGRect.h
        ${source_dir}/svg/SVGSVG.cpp
        ${source_dir}/svg/SVGSVG.h
        )
list(APPEND source ${source_dir}/tinyxml2/tinyxml2.h ${source_dir}/tinyxml2/tinyxml2.cpp)

include

list(APPEND test_source
        ${test_source_dir}/main.cpp)
add_executable(test ${test_source})
add_library(tinysvg ${source})

target_compile_definitions(tinysvg PUBLIC "TINYSVG")

if(${WIN32})
    target_compile_definitions(tinysvg PUBLIC "UNICODE" "_UNICODE")
    target_compile_definitions(test PUBLIC "UNICODE" "_UNICODE")
    target_link_libraries(tinysvg d2d1.lib dwrite.lib ComCtl32.lib)
    set_target_properties(test PROPERTIES WIN32_EXECUTABLE TRUE)
endif(${WIN32})

set_target_properties(tinysvg PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${output_dir})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
