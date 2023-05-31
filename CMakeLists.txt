cmake_minimum_required(VERSION 3.1)
project(pokeclash)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
file(GLOB_RECURSE SRCS "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Add ImGui files
file(GLOB IMGUI_SRCS "${PROJECT_SOURCE_DIR}/external/imgui/*.cpp")
add_library(imgui ${IMGUI_SRCS})
target_include_directories(imgui PUBLIC "${PROJECT_SOURCE_DIR}/external/imgui")

# Add ImGui-SFML binding files
file(GLOB IMGUI_SFML_SRCS "${PROJECT_SOURCE_DIR}/external/imgui-sfml/*.cpp")
add_library(imgui-sfml ${IMGUI_SFML_SRCS})
target_include_directories(imgui-sfml PUBLIC "${PROJECT_SOURCE_DIR}/external/imgui-sfml")
target_link_libraries(imgui-sfml PUBLIC imgui sfml-graphics sfml-audio sfml-window sfml-system)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio sfml-window sfml-system imgui imgui-sfml OpenGL::GL)
