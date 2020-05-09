
add_definitions(-Wno-deprecated-declarations)

set(opengl_SOURCES opengl_engine.cpp opengl_app.cpp opengl_window.cpp)

if (mpv_FOUND)
    set(opengl_SOURCES ${opengl_SOURCES} videowidget.cpp)
endif()

add_library(frontier-opengl SHARED ${opengl_SOURCES})

include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(frontier-opengl frontier ${OPENGL_LIBRARIES} ${mpv_LIBRARIES})

install(TARGETS frontier-opengl DESTINATION lib)

