cmake_minimum_required(VERSION 3.15)
project(DesktopBud CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find raylib
find_package(raylib 4.0.0 QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Main executable
add_executable(DesktopBud
    DesktopBud/main.cpp
    DesktopBud/Sonic/Sonic.cpp
)

# Link libraries
target_link_libraries(DesktopBud raylib)

# Include directories
target_include_directories(DesktopBud PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/DesktopBud
)

# Platform-specific settings
if(UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(DesktopBud X11)
endif()

if(APPLE)
    # macOS
    target_link_libraries(DesktopBud "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

if(WIN32)
    # Windows - raylib handles this
endif()

# Copy assets to build directory (if you have an assets folder)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/bin/assets
    )
    add_dependencies(DesktopBud copy_assets)
endif()

# Copy costume files to build directory
file(GLOB COSTUME_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.png")
if(COSTUME_FILES)
    foreach(FILE ${COSTUME_FILES})
        add_custom_command(TARGET DesktopBud POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${FILE}
            ${CMAKE_BINARY_DIR}/bin/
        )
    endforeach()
endif()
