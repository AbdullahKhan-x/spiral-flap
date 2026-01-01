# rlImGui - Raylib ImGui bindings

set(RLIMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(rlimgui STATIC
    ${RLIMGUI_DIR}/rlImGui.cpp
)

target_include_directories(rlimgui PUBLIC ${RLIMGUI_DIR})

# Link rlimgui with its dependencies
target_link_libraries(rlimgui PUBLIC
    imgui
    raylib
)

# Set C++ standard
target_compile_features(rlimgui PUBLIC cxx_std_17)
