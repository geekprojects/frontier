
#include "wayland.h"

using namespace std;
using namespace Frontier;
using namespace Geek;

FRONTIER_ENGINE(Wayland, Frontier::WaylandEngine)

#define BTN_MOUSE		0x110
#define BTN_LEFT		0x110
#define BTN_RIGHT		0x111
#define BTN_MIDDLE		0x112

static void removeGlobal (void* pVoid, wl_registry* pRegistry, uint32_t i) {}

static const wl_registry_listener registry_listener =
{
    .global = WaylandEngine::globalRegistryHandler,
    .global_remove = removeGlobal
};

static const struct xdg_wm_base_listener xdg_wm_base_listener =
{
    .ping = WaylandEngine::xdgWMPing
};

static const struct wl_seat_listener wl_seat_listener =
{
    .capabilities = WaylandEngine::seatCapabilities,
    .name = WaylandEngine::seatName
};

static const struct wl_pointer_listener wl_pointer_listener =
{
    .enter = WaylandEngine::pointerEnter,
    .leave = WaylandEngine::pointerLeave,
    .motion = WaylandEngine::pointerMotion,
    .button = WaylandEngine::pointerButton,
    .axis = WaylandEngine::pointerAxis,
    .frame = WaylandEngine::pointerFrame,
    .axis_source = WaylandEngine::pointerAxisSource,
    .axis_stop = WaylandEngine::pointerAxisStop,
    .axis_discrete = WaylandEngine::pointerAxisDiscrete,
};

WaylandEngine::WaylandEngine(FrontierApp* app) : FrontierEngine(app)
{

}

WaylandEngine::~WaylandEngine()
{

}

bool WaylandEngine::init()
{
    m_display = wl_display_connect (NULL);
    log(DEBUG, "init: m_display=%p", m_display);
    if (m_display == nullptr)
    {
        log(ERROR, "init: Failed to connect to Wayland display");
        return false;
    }

    m_registry = wl_display_get_registry(m_display);
    log(DEBUG, "init: m_registry=%p", m_registry);
    if (m_registry == nullptr)
    {
        log(ERROR, "init: Failed to get registry");
    }

    wl_registry_add_listener(m_registry, &registry_listener, this);

    log(DEBUG, "init: Calling wl_display_roundtrip...");
    wl_display_roundtrip(m_display);

    log(DEBUG, "init: m_compositor=%p, m_shm=%p, m_xdgBase=%p", m_compositor, m_shm, m_xdgWmBase);

    xdg_wm_base_add_listener(m_xdgWmBase, &xdg_wm_base_listener, this);

    wl_seat_add_listener(m_seat, &wl_seat_listener, this);

    return true;
}

bool WaylandEngine::initWindow(Frontier::FrontierWindow* window)
{
    WaylandWindow* waylandWindow = new WaylandWindow(this, window);

    bool res;
    res = waylandWindow->init();
    if (!res)
    {
        return false;
    }

    window->setEngineWindow(waylandWindow);
    m_windowSurfaceMap.insert(make_pair(waylandWindow->getWlSurface(), waylandWindow));

    return true;
}

bool WaylandEngine::quit(bool force)
{
    return true;
}

bool WaylandEngine::checkEvents()
{
    while (wl_display_dispatch(m_display))
    {
        /* This space deliberately left blank */
    }
    return false;
}

void WaylandEngine::requestUpdate(WaylandEngine* window)
{

}

void WaylandEngine::globalRegistryHandler(
    void* data,
    struct wl_registry* registry,
    uint32_t id,
    const char* interface,
    uint32_t version)
{
    ((WaylandEngine*)data)->registryHandler(interface, id, version);
}

void WaylandEngine::registryHandler(const char* interface, uint32_t id, int version)
{
    log(DEBUG, "registryHandler: interface=%s, id=0x%x, version=%d", interface, id, version);

    if (!strcmp(interface, wl_compositor_interface.name))
    {
        m_compositor = static_cast<wl_compositor*>(wl_registry_bind(m_registry, id, &wl_compositor_interface, 4));
    }
    else if (!strcmp(interface, wl_shm_interface.name))
    {
        m_shm = static_cast<wl_shm*>(wl_registry_bind(m_registry, id, &wl_shm_interface, 1));
    }
    else if (strcmp(interface, xdg_wm_base_interface.name) == 0)
    {
        m_xdgWmBase = static_cast<xdg_wm_base*>(wl_registry_bind(m_registry, id, &xdg_wm_base_interface, 1));
    }
    else if (strcmp(interface, wl_seat_interface.name) == 0)
    {
        m_seat = static_cast<wl_seat*>(wl_registry_bind(m_registry, id, &wl_seat_interface, 7));
    }
}

void WaylandEngine::xdgWMPing(void* data, struct xdg_wm_base* xdg_wm_base, uint32_t serial)
{
    xdg_wm_base_pong(xdg_wm_base, serial);
}

void WaylandEngine::seatCapabilities(void* data, struct wl_seat* wl_seat, uint32_t capabilities)
{
    ((WaylandEngine*)data)->seatCapabilities(wl_seat, capabilities);
}

void WaylandEngine::seatName(void* data, struct wl_seat* wl_seat, const char* name)
{
printf("XXX: WaylandEngine::seatName: name=%s\n", name);
}

void WaylandEngine::seatCapabilities(struct wl_seat* wl_seat, uint32_t capabilities)
{
    bool hasPointer = capabilities & WL_SEAT_CAPABILITY_POINTER;
    if (hasPointer && m_pointer == NULL)
    {
        log(DEBUG, "seatCapabilities: Setting pointer listener...");
        m_pointer = wl_seat_get_pointer(m_seat);
        wl_pointer_add_listener(m_pointer, &wl_pointer_listener, this);
    }
    else if (!hasPointer && m_pointer != NULL)
    {
        wl_pointer_release(m_pointer);
        m_pointer = NULL;
    }
}


void WaylandEngine::pointerEnter(
    void* data,
    struct wl_pointer* wl_pointer,
    uint32_t serial,
    struct wl_surface* surface,
    wl_fixed_t surface_x,
    wl_fixed_t surface_y)
{
    printf("XXX: WaylandEngine::pointerEnter: HERE!\n");
    double x = wl_fixed_to_double(surface_x);
    double y = wl_fixed_to_double(surface_y);
    ((WaylandEngine*)data)->pointerEnter(wl_pointer, serial, surface, x, y);
}

void WaylandEngine::pointerLeave(void* data, struct wl_pointer* wl_pointer, uint32_t serial, struct wl_surface* surface)
{
    printf("XXX: WaylandEngine::pointerLeave: HERE!\n");
}

void WaylandEngine::pointerMotion(
    void* data,
    struct wl_pointer* wl_pointer,
    uint32_t time,
    wl_fixed_t surface_x,
    wl_fixed_t surface_y)
{
    double x = wl_fixed_to_double(surface_x);
    double y = wl_fixed_to_double(surface_y);
    ((WaylandEngine*)data)->pointerMotion(wl_pointer, time, x, y);
}

void WaylandEngine::pointerButton(
    void* data,
    struct wl_pointer* wl_pointer,
    uint32_t serial,
    uint32_t time,
    uint32_t button,
    uint32_t state)
{
    ((WaylandEngine*)data)->pointerButton(wl_pointer, serial, time, button, state);
}

void
WaylandEngine::pointerAxis(void* data, struct wl_pointer* wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{

}

void WaylandEngine::pointerFrame(void* data, struct wl_pointer* wl_pointer)
{

}

void WaylandEngine::pointerAxisSource(void* data, struct wl_pointer* wl_pointer, uint32_t axis_source)
{

}

void WaylandEngine::pointerAxisStop(void* data, struct wl_pointer* wl_pointer, uint32_t time, uint32_t axis)
{

}

void WaylandEngine::pointerAxisDiscrete(void* data, struct wl_pointer* wl_pointer, uint32_t axis, int32_t discrete)
{

}

void WaylandEngine::pointerEnter(
    struct wl_pointer* wl_pointer,
    uint32_t serial,
    struct wl_surface* surface,
    double x,
    double y)
{
    auto it = m_windowSurfaceMap.find(surface);
    if (it == m_windowSurfaceMap.end())
    {
        log(DEBUG, "pointerEnter: Unable to find window for surface: %p", surface);
        return;
    }
    m_currentWindow = it->second;
    m_currentX = x;
    m_currentY = y;
}

void
WaylandEngine::pointerButton(wl_pointer* wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
    log(DEBUG, "pointerButton: button=0x%x, state=0x%x", button, state);

    if (m_currentWindow == nullptr)
    {
        log(WARN, "pointerButton: No current window");
        return;
    }

    MouseButtonEvent* mouseButtonEvent = new MouseButtonEvent();
    mouseButtonEvent->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
    mouseButtonEvent->direction = !!state;

    mouseButtonEvent->buttons = 0;
    if (button == BTN_LEFT)
    {
        mouseButtonEvent->buttons = BUTTON_LEFT;
    }
    else if (button == BTN_RIGHT)
    {
        mouseButtonEvent->buttons = BUTTON_RIGHT;
    }
    mouseButtonEvent->doubleClick = false;

    mouseButtonEvent->x = m_currentX;
    mouseButtonEvent->y = m_currentY;
    log(DEBUG, "pointerButton: few=%p, x=%d, y=%d", m_currentWindow, mouseButtonEvent->x, mouseButtonEvent->y);
    m_currentWindow->getWindow()->handleEvent(mouseButtonEvent);
}

void WaylandEngine::pointerMotion(struct wl_pointer* wl_pointer, uint32_t time, double x, double y)
{
    if (m_currentWindow == nullptr)
    {
        return;
    }

    m_currentX = x;
    m_currentY = y;

    MouseMotionEvent* mouseMotionEvent = new MouseMotionEvent();
    mouseMotionEvent->eventType = FRONTIER_EVENT_MOUSE_MOTION;

    mouseMotionEvent->x = m_currentX;
    mouseMotionEvent->y = m_currentY;

    m_currentWindow->getWindow()->handleEvent(mouseMotionEvent);
}
