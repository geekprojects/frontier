//
// Created by Ian Parker on 25/10/2020.
//

#ifndef FRONTIER_WAYLAND_H
#define FRONTIER_WAYLAND_H

#include <frontier/engine.h>
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"

namespace Frontier
{

class WaylandWindow;

class WaylandEngine : public FrontierEngine
{
 private:
    wl_display* m_display = nullptr;
    wl_registry* m_registry = nullptr;
    wl_compositor* m_compositor = nullptr;
    wl_shm* m_shm = nullptr;
    xdg_wm_base* m_xdgWmBase = nullptr;
    wl_seat* m_seat = nullptr;
    wl_pointer* m_pointer = nullptr;

    std::map<wl_surface*, WaylandWindow*> m_windowSurfaceMap;
    WaylandWindow* m_currentWindow = nullptr;
    double m_currentX;
    double m_currentY;

    void registryHandler(const char* interface, uint32_t id, int version);
    void seatCapabilities(struct wl_seat *wl_seat, uint32_t capabilities);

    void pointerEnter(
        wl_pointer* wl_pointer,
        uint32_t serial,
        wl_surface* surface,
        double x,
        double y);

    void pointerMotion(
        struct wl_pointer* wl_pointer,
        uint32_t time,
        double x,
        double y);

    void pointerButton(
        wl_pointer *wl_pointer,
        uint32_t serial,
        uint32_t time,
        uint32_t button,
        uint32_t state);
 public:
    explicit WaylandEngine(FrontierApp* app);
    ~WaylandEngine() override;

    bool init() override;
    bool initWindow(Frontier::FrontierWindow* window) override;

    bool quit(bool force) override;

    bool checkEvents() override;

    void requestUpdate(WaylandEngine* window);

    wl_display* getDisplay() const
    {
        return m_display;
    }

    wl_compositor* getCompositor() const
    {
        return m_compositor;
    }

    wl_shm* getShm() const
    {
        return m_shm;
    }

    xdg_wm_base* getXdgWmBase() const
    {
        return m_xdgWmBase;
    }


    /*
     * Callbacks
     */
    static void globalRegistryHandler(
        void *data,
        struct wl_registry *registry,
        uint32_t id,
        const char *interface,
        uint32_t version);
    static void xdgWMPing(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial);

    static void seatCapabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities);
    static void seatName(void *data, struct wl_seat *wl_seat, const char *name);

    static void pointerEnter(
        void* data,
        struct wl_pointer* wl_pointer,
        uint32_t serial,
        struct wl_surface* surface,
        wl_fixed_t surface_x,
        wl_fixed_t surface_y);

    static void pointerLeave(
        void* data,
        struct wl_pointer* wl_pointer,
        uint32_t serial,
        struct wl_surface* surface);

    static void pointerMotion(
        void* data,
        struct wl_pointer* wl_pointer,
        uint32_t time,
        wl_fixed_t surface_x,
        wl_fixed_t surface_y);

    static void pointerButton(
        void *data,
        struct wl_pointer *wl_pointer,
        uint32_t serial,
        uint32_t time,
        uint32_t button,
        uint32_t state);
    static void pointerAxis(
        void *data,
        wl_pointer *wl_pointer,
        uint32_t time,
        uint32_t axis,
        wl_fixed_t value);

    static void pointerFrame(void* data, struct wl_pointer* wl_pointer);

    static void pointerAxisSource(
        void* data,
        struct wl_pointer* wl_pointer,
        uint32_t axis_source);

    static void pointerAxisStop(
        void* data,
        struct wl_pointer* wl_pointer,
        uint32_t time,
        uint32_t axis);

    static void pointerAxisDiscrete(
        void* data,
        struct wl_pointer* wl_pointer,
        uint32_t axis,
        int32_t discrete);
};

class WaylandWindow : public FrontierEngineWindow
{
 private:
    wl_surface* m_wlSurface = nullptr;
    xdg_surface* m_xdgSurface = nullptr;
    xdg_toplevel* m_xdgToplevel = nullptr;
    bool m_configured = false;

    uint32_t* m_data = nullptr;
    unsigned int m_dataSize = 0;
    wl_shm_pool* m_pool = nullptr;

    Size m_currentSize = {0, 0};

    bool createBuffer(Size winSize);
    wl_buffer* drawFrame();

    void xdgSurfaceConfigure(xdg_surface *xdg_surface, uint32_t serial);

 public:
    WaylandWindow(FrontierEngine* engine, FrontierWindow* window);
    ~WaylandWindow() override;

    bool init() override;

    void show() override;

    void hide() override;

    bool update() override;

    void setPosition(unsigned int x, unsigned int y) override;

    Geek::Vector2D getPosition() override;

    float getScaleFactor() override;

    void resetCursor() override;

    void updateCursor(Frontier::WindowCursor cursor, int x, int y, int w, int h) override;

    void requestUpdate() override;

    static void xdgSurfaceConfigure(void *data, struct xdg_surface *xdg_surface, uint32_t serial);

    static void wlBufferRelease(void *data, struct wl_buffer *wl_buffer);

    wl_surface* getWlSurface() const
    {
        return m_wlSurface;
    }

};
}

#endif //FRONTIER_WAYLAND_H
