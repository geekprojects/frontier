
add_subdirectory(styles)

list(APPEND libfrontier_srcs
    app.cpp
    engine.cpp
    menu.cpp
    theme.cpp
    window.cpp
    contextmenu.cpp
    icon.cpp
    object.cpp
    layer.cpp
    utils.cpp
    engines/test/test_engine.cpp
    engines/embedded/embedded_window.cpp
    engines/embedded/embedded_engine.cpp
    engines/windowing/windowing_engine.cpp
    engines/windowing/windowing_window.cpp
    widgets/button.cpp
    widgets/iconbutton.cpp
    widgets/checkbox.cpp
    widgets/scrollbar.cpp
    widgets/terminal.cpp
    widgets/combobox.cpp
    widgets/label.cpp
    widgets/scroller.cpp
    widgets/textinput.cpp
    widgets/frame.cpp
    widgets/numberinput.cpp
    widgets/tab.cpp
    widgets/widget.cpp
    widgets/grid.cpp
    widgets/resizeableframe.cpp
    widgets/tabs.cpp
    widgets/date.cpp
    widgets/hsvwheel.cpp
    widgets/colourbutton.cpp
    widgets/list/textlistitem.cpp
    widgets/list/list.cpp
    widgets/list/menulist.cpp
    widgets/list/treelistitem.cpp
    widgets/registry.cpp
    widgets/builder.cpp
    windows/datepicker.cpp
    windows/colourpicker.cpp
)

if (ENGINE MATCHES Cocoa)
    list(APPEND libfrontier_srcs
        engines/cocoa/CocoaEngine.mm
        engines/cocoa/utils.mm
        engines/cocoa/CocoaWindow.mm
    )
    add_definitions(-DFRONTIER_ENGINE_COCOA -Wno-deprecated-declarations)
    set(ENGINE_LIBRARIES "-framework AppKit")
elseif (ENGINE MATCHES X11)
    list(APPEND libfrontier_srcs
        engines/x11/x11_engine.cpp
        engines/x11/x11_window.cpp
    )
    add_definitions(-DFRONTIER_ENGINE_X11 -I${X11_INCLUDE_DIR})
    set(ENGINE_LIBRARIES ${X11_LIBRARIES})
elseif (ENGINE MATCHES SDL)
    list(APPEND libfrontier_srcs
        engines/sdl/sdl_engine.cpp
        engines/sdl/sdl_window.cpp
    )
    add_definitions(-DFRONTIER_ENGINE_SDL ${sdl2_CFLAGS})
    set(ENGINE_LIBRARIES ${sdl2_LDFLAGS})
elseif(ENGINE MATCHES Wayland)
    list(APPEND libfrontier_srcs
        engines/wayland/wayland_engine.cpp
        engines/wayland/wayland_window.cpp
        engines/wayland/xdg-shell-protocol.c
        engines/wayland/wayland.h
    )
    add_definitions(-DFRONTIER_ENGINE_WAYLAND ${waylandclient_CFLAGS})
    set(ENGINE_LIBRARIES ${waylandclient_LDFLAGS})
endif()

add_definitions(-DFONTSDIR=${DATADIR}/fonts)

add_library(frontier SHARED ${libfrontier_srcs})

if(LIBRT)
    target_link_libraries(target_name ${LIBRT})
endif()

target_link_libraries(frontier ${libgeek_LDFLAGS} ${ANTLR4_LIBRARY} ${ENGINE_LIBRARIES} styles -lutil)

install(TARGETS frontier DESTINATION lib)

