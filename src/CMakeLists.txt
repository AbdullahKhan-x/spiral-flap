add_executable(spiral-flap
    main.cpp
    gameloop.cpp
)

target_include_directories(spiral-flap PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(spiral-flap PRIVATE
    rlimgui
    imgui
    raylib
)

set_target_properties(spiral-flap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
