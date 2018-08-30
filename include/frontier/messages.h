#ifndef __FRONTIER_EVENTS_H_
#define __FRONTIER_EVENTS_H_

namespace Frontier {

enum MessageType
{
    FRONTIER_MSG_INPUT = 1,
    FRONTIER_MSG_UI = 2,
    FRONTIER_MSG_APP = 1000
};

struct Message
{
    uint32_t messageType;
};

/*
 * User Input Events
 */

enum InputMessageType
{
    FRONTIER_MSG_INPUT_KEY = 1,
    FRONTIER_MSG_INPUT_MOUSE_BUTTON = 2,
    FRONTIER_MSG_INPUT_MOUSE_MOTION = 3
};

struct InputMessage : public Message
{
    InputMessageType inputMessageType;

    union
    {
        struct
        {
            bool direction;
            uint32_t key;
        } key;
        struct
        {
            uint32_t x;
            uint32_t y;
        } motion;
        struct
        {
            uint32_t x;
            uint32_t y;

            bool direction;
            uint8_t button;
            bool doubleClick;
        } button;
    } event;
};


/*
 * UI/Widget generated events
 */
class Widget;

struct UIMessage : public Frontier::Message
{
    int uiMessageType;
    Widget* widget;
    Frontier::Message* source;
    struct
    {
        bool state;
    } button;
    struct
    {
        int selected;
        int itemY;
    } list;
};

#define FRONTIER_MSG_UI_BUTTON_PRESSED 0x1000
#define FRONTIER_MSG_UI_LIST_SELECTED 0x2000


/*
 * Application Specific Messages
 */

#define FRONTIER_MSG_APP_QUIT 1

struct AppMessage : public Message
{
    uint32_t appMessageType;
};


};

#endif

