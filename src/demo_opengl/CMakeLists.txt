add_definitions(-Wno-deprecated-declarations)
add_executable(demo_opengl main.cpp)
target_link_libraries(demo_opengl frontier frontier-opengl ${GLUT_LIBRARIES})

