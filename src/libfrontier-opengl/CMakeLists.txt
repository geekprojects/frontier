
add_definitions(-Wno-deprecated-declarations)

add_library(frontier-opengl SHARED opengl_engine.cpp opengl_app.cpp opengl_window.cpp)

include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(frontier-opengl frontier ${OPENGL_LIBRARIES})

install(TARGETS frontier-opengl DESTINATION lib)

