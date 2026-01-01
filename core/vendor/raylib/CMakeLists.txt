add_library(raylib STATIC IMPORTED GLOBAL)

set_target_properties(raylib PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(WIN32)
    set_property(TARGET raylib
                 PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/raylib.lib")
elseif(UNIX)
    set_property(TARGET raylib
                 PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/libraylib.a")
endif()
