add_executable(spiral-flap
    main.cpp
    gameloop.cpp
)

target_include_directories(CalculatorApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(CalculatorApp PRIVATE
    raylib
)

set_target_properties(CalculatorApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
