cmake_minimum_required(VERSION 3.29)
project(breakout C)

set(CMAKE_C_STANDARD 99)

set(PROJECT_OUTPUT_BIN_DIR "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_BIN_DIR}")

include(FetchContent)
FetchContent_Declare(SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.8
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SDL)

add_executable(${PROJECT_NAME} WIN32
        src/main.c
        src/game.h
        src/game.c
        src/utils/vec2.c
        src/utils/vec2.h)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
