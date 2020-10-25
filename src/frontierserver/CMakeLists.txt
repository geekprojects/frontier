add_definitions(-DFRONTIER_SRC=${PROJECT_SOURCE_DIR})

add_executable(frontierserver main.cpp)

target_link_libraries(frontierserver frontier)