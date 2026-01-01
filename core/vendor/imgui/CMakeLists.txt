# ImGui doesn't come with CMake support, so we build it as a library

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_DIR})

# Set C++ standard for imgui
target_compile_features(imgui PUBLIC cxx_std_17)
