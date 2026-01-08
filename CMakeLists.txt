cmake_minimum_required(VERSION 3.6.0)
project(Intro)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 8)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Wpedantic -g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(yaml-cpp-0.8.0)


set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Window.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine.cpp
    ${PROJECT_SOURCE_DIR}/src/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/BasicGeometry.cpp
    ${PROJECT_SOURCE_DIR}/src/Settings.cpp

)

FILE(GLOB MyCSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

add_executable(program ${MyCSources})

target_link_libraries(program PUBLIC

    mingw32
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    yaml-cpp::yaml-cpp

)
