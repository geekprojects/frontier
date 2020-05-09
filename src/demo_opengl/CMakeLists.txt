
add_definitions(-Wno-deprecated-declarations)
if (mpv_FOUND)
    add_definitions(-DMPV_FOUND=1)
endif()

add_executable(demo_opengl main.cpp)
target_link_libraries(demo_opengl frontier frontier-opengl ${GLUT_LIBRARIES})

