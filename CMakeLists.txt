cmake_minimum_required(VERSION 3.10)
project(VersaMachina)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

#spdlog
add_library(spdlog::spdlog_header_only INTERFACE IMPORTED GLOBAL)
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE vendor/spdlog/include)
add_library(spdlog::spdlog ALIAS spdlog)

#DearImGui
# ImGui
file(GLOB IMGUI_SOURCES
    vendor/imgui/*.cpp
    vendor/imgui/misc/cpp/*.cpp
    vendor/imgui/backends/imgui_impl_sdl2.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/ImGuizmo/*.cpp
)

#YAML-CPP
add_subdirectory(vendor/yaml)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    vendor/imgui
    vendor/imgui/misc/cpp
    vendor/imgui/backends
    vendor/SDL2/include
    vendor/ImGuizmo
)

file(GLOB_RECURSE SOURCES src/*.cpp)

# Main application
add_executable(versa ${SOURCES} vendor/tinyfd/tinyfiledialogs.c )
target_include_directories(versa PRIVATE
    include/
    vendor/spdlog/include
    vendor/entt/single_include
    vendor/SDL2/include
    vendor/glm
    vendor/imgui
    vendor/ImGuizmo
    vendor/yaml/include
    vendor/tinyfd
    vendor/PlatformDirs/include
    # vendor/json/single_include
)
target_link_libraries(versa PUBLIC
    spdlog::spdlog
    SDL2
    imgui
    OpenGL::GL
    yaml-cpp
)
