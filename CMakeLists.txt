cmake_minimum_required(VERSION 3.16)
project(BitService-2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OUTPUT_FILENAME "main")

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    source/*.cpp
)

add_executable(${OUTPUT_FILENAME} ${PROJECT_SOURCES})

target_include_directories(${OUTPUT_FILENAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/lang
        ${CMAKE_CURRENT_SOURCE_DIR}/config
)

find_package(SFML 2.5 REQUIRED
    COMPONENTS
        graphics
        window
        system
        audio
)

target_link_libraries(${OUTPUT_FILENAME}
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

# Uncomment if debug mode needed
# target_compile_definitions(${OUTPUT_FILENAME} PRIVATE DEBUG_MODE)

if (WIN32)
    target_compile_definitions(${OUTPUT_FILENAME} PRIVATE NOMINMAX)
endif()