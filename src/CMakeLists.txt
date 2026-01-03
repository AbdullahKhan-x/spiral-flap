cmake_minimum_required(VERSION 3.10)
project(spiral-flap)

# Define the executable once
add_executable(spiral-flap
    main.cpp
    gameloop.cpp
    map.cpp
)

# Set up include directories
target_include_directories(spiral-flap PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core/vendor/raylib/include
)

# Link basic libraries
target_link_libraries(spiral-flap PRIVATE
    raylib
    imgui
    rlimgui
)

# Link Windows-specific system libraries
if(WIN32)
    target_link_libraries(spiral-flap PRIVATE
        winmm
        gdi32
        opengl32
    )
endif()

# Set output directory to the /bin folder
set_target_properties(spiral-flap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)