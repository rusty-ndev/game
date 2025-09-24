cmake_minimum_required(VERSION 3.16)
project(MyGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)

set(SOURCES
    src/main.cpp
    src/PlatformLayer/platform_glfw.cpp
)

add_executable(my_game ${SOURCES})

# Add include paths
target_include_directories(my_game PRIVATE
    ${GLFW_INCLUDE_DIRS}
    src/PlatformLayer
)

# Link libraries
target_link_libraries(my_game PRIVATE
    ${GLFW_LIBRARIES}
    OpenGL::GL
)

