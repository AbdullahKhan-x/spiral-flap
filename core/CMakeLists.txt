# Add raylib
add_subdirectory(vendor/raylib)

# Build rlimgui (header only? library?)
add_library(rlimgui INTERFACE)
target_include_directories(rlimgui INTERFACE vendor/rlimgui)

# Build imgui (Assuming it has cpp sources)
file(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)
add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC vendor/imgui)
