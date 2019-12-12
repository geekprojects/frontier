cmake_minimum_required(VERSION 3.10)

include(CheckSymbolExists)
include(CheckIncludeFile)

# set the project name
project(frontier VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(FLAGS_COMMON "-Wall -Werror")
SET(CMAKE_C_FLAGS "${FLAGS_COMMON}")
SET(CMAKE_CXX_FLAGS "${FLAGS_COMMON}")
SET(CMAKE_C_FLAGS_DEBUG "${FLAGS_COMMON} -O0 -g  -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer")
SET(CMAKE_CXX_FLAGS_DEBUG "${FLAGS_COMMON} -O0 -g -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer")
SET(CMAKE_C_FLAGS_RELEASE "${FLAGS_COMMON} -O3")
SET(CMAKE_CXX_FLAGS_RELEASE "${FLAGS_COMMON} -O3")

find_package(PkgConfig REQUIRED)
find_package(Doxygen COMPONENTS dot)

# Common requirements
pkg_check_modules(libgeek REQUIRED libgeek)
pkg_check_modules(freetype2 REQUIRED freetype2)

find_library(ANTLR4_LIBRARY NAMES antlr4-runtime )
find_path(antlr4_INCLUDE_BASE NAMES antlr4-runtime/antlr4-runtime.h)
if(antlr4_INCLUDE_BASE)
    set(ANTLR4_INCLUDE ${antlr4_INCLUDE_BASE}/antlr4-runtime)
else()
    message(FATAL_ERROR "Unable to find antlr4 headers")
endif()


add_definitions(${libgeek_CFLAGS} ${freetype2_CFLAGS})

# Optional dependencies
include(FindOpenGL)
include(FindGLUT)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${ANTLR4_INCLUDE}
)

# Engines
if (NOT ENGINE)
    message(STATUS "Choosing engine for system: ${CMAKE_SYSTEM_NAME}")
    if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        SET(ENGINE "Cocoa")
    else()
        SET(ENGINE "SDL")
    endif()
else()
    message(STATUS "User selected engine: ${ENGINE}")
endif()

message(STATUS "Engine: ${ENGINE}")

if(ENGINE MATCHES "Cocoa")

elseif(ENGINE MATCHES "SDL")
    pkg_check_modules(sdl2 REQUIRED sdl2)
endif()

set(DATADIR ${CMAKE_INSTALL_PREFIX}/share/libfrontier)

add_subdirectory(src/libfrontier)
add_subdirectory(src/demo)
add_subdirectory(data)

if(OPENGL_FOUND)
    add_subdirectory(src/libfrontier-opengl)
    if(GLUT_FOUND)
        add_subdirectory(src/demo_opengl)
    endif()
endif()

install(DIRECTORY include/frontier DESTINATION include FILES_MATCHING PATTERN "*.h" )

set(PKGCONFIG_CFLAGS_LIST -I${CMAKE_INSTALL_PREFIX}/include ${libgeek_CFLAGS})
string(REPLACE ";" " " PKGCONFIG_CFLAGS "${PKGCONFIG_CFLAGS_LIST}")
set(PKGCONFIG_LDFLAGS_LIST -L${CMAKE_INSTALL_PREFIX}/lib -lfrontier ${libgeek_LDFLAGS})
string(REPLACE ";" " " PKGCONFIG_LDFLAGS "${PKGCONFIG_LDFLAGS_LIST}")

configure_file(libfrontier.pc.in libfrontier.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libfrontier.pc DESTINATION "lib${LIB_SUFFIX}/pkgconfig")

if (DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_EXTRACT_ALL YES)

    doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}/include
        COMMENT "Generate man pages"
    )
endif()


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${frontier_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${frontier_VERSION_MINOR}")
include(CPack)

