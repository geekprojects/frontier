
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
    utils.cpp
    engines/test/test_engine.cpp
    engines/embedded/embedded_window.cpp
    engines/embedded/embedded_engine.cpp
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
elseif (ENGINE MATCHES SDL)
    list(APPEND libfrontier_srcs
        engines/sdl/sdl_engine.cpp
        engines/sdl/sdl_window.cpp
    )
    add_definitions(-DFRONTIER_ENGINE_SDL ${sdl2_CFLAGS})
    set(ENGINE_LIBRARIES ${sdl2_LDFLAGS})
endif()

add_definitions(-DFONTSDIR=${DATADIR}/fonts)

add_library(frontier SHARED ${libfrontier_srcs})

target_link_libraries(frontier ${libgeek_LDFLAGS} ${ANTLR4_LIBRARY} ${ENGINE_LIBRARIES} styles -lutil)

install(TARGETS frontier DESTINATION lib)

