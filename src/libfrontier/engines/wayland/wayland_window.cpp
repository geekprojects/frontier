#include "wayland.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace Frontier;
using namespace Geek;

static void randname(char *buf)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long r = ts.tv_nsec;
    for (int i = 0; i < 6; ++i)
    {
        buf[i] = 'A'+(r&15)+(r&16)*2;
        r >>= 5;
    }
}

static int create_shm_file(void)
{
    int retries = 100;
    do {
        char name[] = "/wl_shm-XXXXXX";
        randname(name + sizeof(name) - 7);
        --retries;
        int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
        if (fd >= 0) {
            shm_unlink(name);
            return fd;
        }
    } while (retries > 0 && errno == EEXIST);
    return -1;
}

static int allocate_shm_file(size_t size)
{
    int fd = create_shm_file();
    if (fd < 0)
        return -1;
    int ret;
    do
    {
        ret = ftruncate(fd, size);
    } while (ret < 0 && errno == EINTR);

    if (ret < 0)
    {
        close(fd);
        return -1;
    }
    return fd;
}

static const struct xdg_surface_listener xdg_surface_listener =
{
    .configure = WaylandWindow::xdgSurfaceConfigure
};

static const struct wl_buffer_listener wl_buffer_listener =
{
    .release = WaylandWindow::wlBufferRelease
};

WaylandWindow::WaylandWindow(FrontierEngine* engine, FrontierWindow* window) : FrontierEngineWindow(engine, window)
{

}

WaylandWindow::~WaylandWindow()
{

}

bool WaylandWindow::init()
{
    WaylandEngine* engine = (WaylandEngine*)getEngine();
    m_wlSurface = wl_compositor_create_surface(engine->getCompositor());
    m_xdgSurface = xdg_wm_base_get_xdg_surface(engine->getXdgWmBase(), m_wlSurface);
    log(DEBUG, "init: m_wlSurface=%p, m_xdgSurface=%p", m_wlSurface, m_xdgSurface);

    xdg_surface_add_listener(m_xdgSurface, &xdg_surface_listener, this);

    m_xdgToplevel = xdg_surface_get_toplevel(m_xdgSurface);

    xdg_toplevel_set_title(m_xdgToplevel, "Frontier!!");
    wl_surface_commit(m_wlSurface);

    return true;
}

void WaylandWindow::show()
{
    FrontierEngineWindow::show();
}

void WaylandWindow::hide()
{
    FrontierEngineWindow::hide();
}

bool WaylandWindow::update()
{
    log(DEBUG, "update: surface=%p", m_window->getSurface());
    if (m_window->getSurface() == NULL || m_window->getSurface()->getData() == NULL)
    {
        return true;
    }

    Size winSize = m_window->getSize();
    xdg_surface_set_window_geometry(m_xdgSurface, 0, 0, (int32_t)winSize.width, (int32_t)winSize.height);

    if (m_configured)
    {
        log(DEBUG, "update: Redrawing...");
        drawFrame();
        wl_surface_damage_buffer(m_wlSurface, 0, 0, INT32_MAX, INT32_MAX);
        wl_surface_commit(m_wlSurface);
    }

    return true;
}

void WaylandWindow::setPosition(unsigned int x, unsigned int y)
{
    FrontierEngineWindow::setPosition(x, y);
}

Vector2D WaylandWindow::getPosition()
{
    return FrontierEngineWindow::getPosition();
}

float WaylandWindow::getScaleFactor()
{
    return FrontierEngineWindow::getScaleFactor();
}

void WaylandWindow::resetCursor()
{
    FrontierEngineWindow::resetCursor();
}

void WaylandWindow::updateCursor(Frontier::WindowCursor cursor, int x, int y, int w, int h)
{
    FrontierEngineWindow::updateCursor(cursor, x, y, w, h);
}

void WaylandWindow::requestUpdate()
{
    log(DEBUG, "requestUpdate: Here!");
    //wl_surface_damage_buffer(m_wlSurface, 0, 0, INT32_MAX, INT32_MAX);
    update();
}

void WaylandWindow::xdgSurfaceConfigure(void* data, struct xdg_surface* xdg_surface, uint32_t serial)
{
    ((WaylandWindow*)data)->xdgSurfaceConfigure(xdg_surface, serial);
}

void WaylandWindow::xdgSurfaceConfigure(xdg_surface* xdg_surface, uint32_t serial)
{
    log(DEBUG, "xdgSurfaceConfigure: here");
    xdg_surface_ack_configure(xdg_surface, serial);

    drawFrame();
    m_configured = true;
}

wl_buffer* WaylandWindow::drawFrame()
{
    Size winSize = m_window->getSize();
    if (m_currentSize != winSize)
    {
        bool res;
        res = createBuffer(winSize);
        if (!res)
        {
            return NULL;
        }
        m_currentSize = winSize;
    }

    log(DEBUG, "drawFrame: Drawing!");
    memcpy(m_data, m_window->getSurface()->getData(), winSize.width * winSize.height * 4);

    wl_buffer* buffer = wl_shm_pool_create_buffer(
        m_pool,
        0,
        winSize.width,
        winSize.height,
        winSize.width * 4,
        WL_SHM_FORMAT_XRGB8888);
//wl_shm_pool_destroy(m_pool);
//close(fd);
    wl_buffer_add_listener(buffer, &wl_buffer_listener, NULL);

    wl_surface_attach(m_wlSurface, buffer, 0, 0);
    wl_surface_commit(m_wlSurface);

    return buffer;
}

bool WaylandWindow::createBuffer(Size winSize)
{
    log(DEBUG, "createBuffer: Creating buffer!");
    int stride = winSize.width * 4;
    m_dataSize = stride * winSize.height;

    int fd = allocate_shm_file(m_dataSize);
    if (fd == -1)
    {
        return false;
    }

    m_data = static_cast<uint32_t*>(mmap(
        NULL,
        m_dataSize,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0));
    if (m_data == MAP_FAILED)
    {
        close(fd);
        return false;
    }

    WaylandEngine* engine = (WaylandEngine*)getEngine();
    m_pool = wl_shm_create_pool(engine->getShm(), fd, m_dataSize);

    return true;
}

void WaylandWindow::wlBufferRelease(void* data, struct wl_buffer* wl_buffer)
{
    wl_buffer_destroy(wl_buffer);
}

