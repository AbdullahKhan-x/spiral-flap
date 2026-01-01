# Imgui subdirectory (has its own CMakeLists.txt)
add_subdirectory(vendor/imgui)

# rlImGui subdirectory (has its own CMakeLists.txt)
add_subdirectory(vendor/rlimgui)

# Raylib (pre-built)
add_library(raylib STATIC IMPORTED)
if(WIN32)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/lib/libraylib.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/include"
    )
elseif(UNIX)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/lib/libraylib.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/include"
    )
endif()
