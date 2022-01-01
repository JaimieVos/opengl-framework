cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(opengl-framework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

file(GLOB_RECURSE sources
	"src/*.h"
	"src/*.cpp"
)

add_executable(opengl-framework ${sources})

foreach(source IN LISTS sources)
    get_filename_component(source_path "${source}" PATH ABSOLUTE)

    file(RELATIVE_PATH
        item_path_rel
        ${PROJECT_SOURCE_DIR}
        ${source_path})

    source_group("${item_path_rel}" FILES "${source}")
endforeach()

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw EXCLUDE_FROM_ALL)
target_link_libraries(opengl-framework PRIVATE glfw)

# GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glew-cmake EXCLUDE_FROM_ALL)
target_link_libraries(opengl-framework PRIVATE libglew_static)

# GLM
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glm EXCLUDE_FROM_ALL)
target_link_libraries(opengl-framework PRIVATE glm)