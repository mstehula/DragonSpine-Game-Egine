cmake_minimum_required(VERSION 2.8)

project(TEST_PROJECT)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/obj)

add_definitions(-DBOOST_LOG_DYN_LINK)
add_definitions(-DBOOST_TEST_DYN_LINK)

find_package(X11)
find_package(OpenGL REQUIRED)
find_package(Boost COMPONENTS system unit_test_framework log REQUIRED)
find_library(PTHREAD_LIBRARY pthread)
find_library(M_LIBRARY m)
find_library(GLU_LIBRARY GLU)
find_library(GLEW_LIBRARY GLEW)
find_library(GLFW_LIBRARY glfw)

set(INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/include"
    ${Boost_INCLUDE_DIRS}
)

set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)

set(ENGINE_DIR ${PROJECT_SOURCE_DIR}/engine)
set(ENGINE_SOURCES
    "${ENGINE_DIR}/Engine.cpp"
)

set(SYSTEMS_DIR ${PROJECT_SOURCE_DIR}/systems)
set(SYSTEMS_SOURCES
    "${SYSTEMS_DIR}/GraphicsSystem.cpp"
    "${SYSTEMS_DIR}/ObjectSystem.cpp"
    "${SYSTEMS_DIR}/WindowSystem.cpp"
)

set(ENGINE_DEPENDS
    ${ENGINE_SOURCES}
    ${SYSTEMS_SOURCES}
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

link_libraries(
    ${X11_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${PTHREAD_LIBRARY}
    ${M_LIBRARY}
    ${GLU_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
)

add_custom_target(tests)
add_executable(EngineTest ${TEST_DIR}/EngineTest.cpp ${ENGINE_DEPENDS})
add_dependencies(tests EngineTest)

add_executable(DODArrayTest ${ENGINE_DEPENDS} ${TEST_DIR}/DODArrayTest.cpp)
add_dependencies(tests DODArrayTest)
