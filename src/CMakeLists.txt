add_executable(spiral-flap
    main.cpp
    gameloop.cpp
)

target_include_directories(spiral-flap PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core/vendor/raylib/include
)

target_link_libraries(spiral-flap PRIVATE
    raylib
    imgui
    rlimgui
)

set_target_properties(spiral-flap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

add_executable(spiral-flap
    main.cpp
    gameloop.cpp
)

target_include_directories(spiral-flap PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core/vendor/raylib/include
)

target_link_libraries(spiral-flap PRIVATE
    raylib
    imgui
    rlimgui
)

if(WIN32)
    target_link_libraries(spiral-flap PRIVATE
        winmm
        gdi32
        opengl32
    )
endif()

set_target_properties(spiral-flap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)