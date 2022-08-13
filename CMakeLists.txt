cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeBuild")

project(ComputationalMethods LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_definitions(-DUNICODE -D_UNICODE)
if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()
add_compile_definitions(PROJET_DIR="${PROJECT_SOURCE_DIR}/")

file(GLOB_RECURSE MATH_FILE CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/math/*.h"
    "${PROJECT_SOURCE_DIR}/math/*.inl"
    "${PROJECT_SOURCE_DIR}/math/*.cpp")

file(GLOB_RECURSE TOOL_FILE CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/tool/*.h"
    "${PROJECT_SOURCE_DIR}/tool/*.inl"
    "${PROJECT_SOURCE_DIR}/tool/*.cpp")

file(GLOB_RECURSE MAIN_FILE CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/main/*.cpp")

source_group(TREE ${PROJECT_SOURCE_DIR}/math FILES ${MATH_FILE})
source_group(TREE ${PROJECT_SOURCE_DIR}/tool FILES ${TOOL_FILE})
source_group(TREE ${PROJECT_SOURCE_DIR}/main FILES ${MAIN_FILE})

add_library(Math STATIC ${MATH_FILE})
target_include_directories(Math PUBLIC ${PROJECT_SOURCE_DIR})
set_target_properties(Math PROPERTIES FOLDER "Math")

add_library(Tool STATIC ${TOOL_FILE})
target_include_directories(Tool PUBLIC ${PROJECT_SOURCE_DIR})
set_target_properties(Tool PROPERTIES FOLDER "Tool")

foreach(main ${MAIN_FILE})
    string(REGEX MATCHALL "[0-9A-Za-z_]*.cpp" tmp ${main})
    string(REGEX REPLACE ".cpp" "" file_name ${tmp})

    add_executable(${file_name} ${main})
    target_link_libraries(${file_name} PUBLIC Math)
    target_include_directories(${file_name} PUBLIC ${PROJECT_SOURCE_DIR})
    target_link_libraries(${file_name} PUBLIC Tool)
    target_include_directories(${file_name} PUBLIC ${PROJECT_SOURCE_DIR})
    set_target_properties(${file_name} PROPERTIES FOLDER "Main")
endforeach()


# VS startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT make_lu)