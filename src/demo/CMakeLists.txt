
add_definitions(-DFRONTIER_SRC=${PROJECT_SOURCE_DIR})

add_executable(demo main.cpp)

target_link_libraries(demo frontier)

