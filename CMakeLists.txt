cmake_minimum_required(VERSION 2.8)

project(TEST_PROJECT)

#

find_package(X11)
find_package(OpenGL REQUIRED)
find_library(M_LIBRARY m)
find_library(GLU_LIBRARY GLU)
find_library(GLEW_LIBRARY GLEW)
find_library(GLFW_LIBRARY glfw)

set(INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/include"
    ${INCLUDE_DIRS}
)

include_directories(
    ${INCLUDE_DIRS}
)

if(UNIX)
    set(INCLUDE_DIRS
        "/usr/include"
        "/usr/local/include"
    )
else(UNIX)
    message("This is not a *nix platform")
endif(UNIX)

add_executable(test test.cpp)

target_link_libraries(
    test
    ${X11_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${M_LIBRARY}
    ${GLU_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
)
