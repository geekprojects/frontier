
ADD_LIBRARY(styles STATIC
    css3BaseListener.cpp
    css3Listener.cpp
    cssparser.cpp
    css3Lexer.cpp
    css3Parser.cpp
    styleengine.cpp
)

add_definitions(-DCSSDIR=${DATADIR})
add_definitions(-Wno-error -Wno-unknown-warning-option -Wno-defaulted-function-deleted)

