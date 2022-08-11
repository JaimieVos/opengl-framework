cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(opengl-framework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

file(GLOB_RECURSE sources
    "src/*.h"
    "src/*.cpp"
	"assets/*.vert"
	"assets/*.frag"
)

add_executable(opengl-framework ${sources})

target_include_directories(opengl-framework PUBLIC 
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/vendor/stb_image
)

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

# Assimp
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/assimp EXCLUDE_FROM_ALL)
target_include_directories(opengl-framework PUBLIC {PROJECT_SOURCE_DIR}/assimp/include)
target_link_libraries(opengl-framework PRIVATE assimp)

# ImGUI
set(imgui_sources
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
)

set(imgui_headers
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imconfig.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_internal.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imstb_rectpack.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imstb_textedit.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imstb_truetype.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.h
)

add_library(ImGui STATIC
    ${imgui_sources}
    ${imgui_headers}
)

target_include_directories(ImGui PUBLIC
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/imgui
)

target_link_libraries(opengl-framework PRIVATE ImGui)

# Assets folder
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)