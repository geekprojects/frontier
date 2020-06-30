
#include "x11_engine.h"

#include <X11/Xutil.h>
#include <X11/Xmd.h>
#include <X11/extensions/XShm.h>

#include <sys/ipc.h>
#include <sys/shm.h>

using namespace Frontier;
using namespace Geek;

X11FrontierWindow::X11FrontierWindow(FrontierEngine* engine, FrontierWindow* window)
    : FrontierEngineWindow(engine, window)
{
    m_xImage = NULL;
    m_xImageData = NULL;
    m_size.set(0, 0);

    memset(&m_shminfo, 0, sizeof(m_shminfo));
}

X11FrontierWindow::~X11FrontierWindow()
{
    Display* dpy = ((X11Engine*)getEngine())->getDisplay();
    if (m_shminfo.shmid != 0)
    {
        XShmDetach(dpy, &m_shminfo );
        shmctl(m_shminfo.shmid, IPC_RMID, 0 );
    }
    if (m_shminfo.shmaddr != NULL && m_shminfo.shmaddr != (void*)-1)
    {
        shmdt(m_shminfo.shmaddr);
    }
    if (m_xImage != NULL)
    {
        XDestroyImage(m_xImage);
    }
}


bool X11FrontierWindow::init()
{
    X11Engine* engine = (X11Engine*)getEngine();
    Display* dpy = ((X11Engine*)getEngine())->getDisplay();

    int s = DefaultScreen(dpy);

    m_x11Window = XCreateSimpleWindow(dpy, RootWindow(dpy, s), 10, 10, 660, 200, 1, BlackPixel(dpy, s), WhitePixel(dpy, s));

    if (!m_window->hasBorder())
    {
        MotifWmHints hints;
        memset(&hints, 0, sizeof(hints));
        hints.flags = MWM_HINTS_DECORATIONS;
        hints.decorations = MWM_DECOR_MENU;
        Atom motifHints = XInternAtom(dpy, "_MOTIF_WM_HINTS", 0);
        XChangeProperty(dpy, m_x11Window, motifHints, motifHints, 32,
        PropModeReplace, (uint8_t*)&hints, 5);
    }

    XGCValues values;
    unsigned long valuemask = GCCapStyle | GCJoinStyle;
    values.cap_style = CapButt;
    values.join_style = JoinBevel;
    m_gc = XCreateGC(dpy, m_x11Window, valuemask, (XGCValues*)&values);
    if (m_gc == NULL)
    {
        log(ERROR, "Failed to create GC");
        return false;
    }

    long mask =
        StructureNotifyMask |
        ExposureMask |
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        KeyPressMask |
        KeyReleaseMask;

    XSelectInput(dpy, m_x11Window, mask);

    XStoreName(dpy, m_x11Window, Utils::wstring2string(m_window->getTitle()).c_str());

    XSetWMProtocols(dpy, m_x11Window, engine->getWMDeleteWindow(), 1);  

    return true;
}

void X11FrontierWindow::show()
{
    Display* dpy = ((X11Engine*)getEngine())->getDisplay();

    XMapWindow(dpy, m_x11Window);
}

void X11FrontierWindow::hide()
{
    Display* dpy = ((X11Engine*)getEngine())->getDisplay();

    XUnmapWindow(dpy, m_x11Window);
}

bool X11FrontierWindow::update()
{
    if (m_window->getSurface() == NULL || m_window->getSurface()->getData() == NULL)
    {
        return true;
    }

    X11Engine* engine = (X11Engine*)getEngine();
    Display* dpy = engine->getDisplay();

    Size winSize = m_window->getSize();

    int len = winSize.width * winSize.height * 4;
    if (m_xImage == NULL || m_size != winSize)
    {
        m_size = winSize;
        XResizeWindow(dpy, m_x11Window, winSize.width, winSize.height);

        if (engine->useShm())
        {

            if (m_xImage != NULL)
            {
                log(DEBUG, "update: Freeing...");
                XShmDetach(dpy, &m_shminfo );
                XDestroyImage(m_xImage);
                shmdt(m_shminfo.shmaddr);
                shmctl(m_shminfo.shmid, IPC_RMID, 0 );
            }

            m_xImage = XShmCreateImage(
                dpy,
                engine->getVisualInfo()->visual,
                24,
                ZPixmap,
                NULL,
                &m_shminfo,
                m_size.width,
                m_size.height);
            if (m_xImage == NULL)
            {
                log(ERROR, "update: Failed to create XImage");
                return false;
            }

            m_shminfo.shmid = shmget(IPC_PRIVATE, len, IPC_CREAT | 0777);
            if (m_shminfo.shmid < 0)
            {
                log(ERROR, "update: Shared memory error (shmget): %s", strerror(errno));
                XDestroyImage(m_xImage);
                m_xImage = NULL;
                return false;
            }

            m_shminfo.shmaddr = m_xImage->data = (char*)shmat( m_shminfo.shmid, 0, 0 );
            log(DEBUG, "update: m_shminfo.shmaddr=%p", m_shminfo.shmaddr);
            if (m_shminfo.shmaddr == (void*)-1)
            {
                log(ERROR, "update: Failed to map shared memory: %s", strerror(errno));
                return false;
            }
            //m_shminfo.readOnly = True; 

            XShmAttach( dpy, &m_shminfo );
            XSync( dpy, False );

            //shmctl( m_shminfo.shmid, IPC_RMID, 0 ); /* nobody else needs it */
        }
        else
        {
            if (m_xImage != NULL)
            {
                XDestroyImage(m_xImage);
            }

            m_xImageData = (char*)malloc(len);
            m_xImage = XCreateImage(
                dpy,
                CopyFromParent,
                24,
                ZPixmap,
                0,
                (char*)m_xImageData,
                m_size.width,
                m_size.height,
                32,
                0);
        }
    }


    if (engine->useShm())
    {
        memcpy(m_xImage->data, m_window->getSurface()->getData(), len);
        XShmPutImage(
            dpy,
            m_x11Window,
            m_gc,
            m_xImage,
            0, 0,
            0, 0,
            m_size.width, m_size.height,
            False);
    }
    else
    {
        memcpy(m_xImageData, m_window->getSurface()->getData(), len);
        XPutImage(
            dpy,
            m_x11Window,
            m_gc,
            m_xImage,
            0, 0,
            0, 0,
            m_size.width, m_size.height);
    }

    return true;
}

void X11FrontierWindow::setPosition(unsigned int x, unsigned int y)
{
}

void X11FrontierWindow::requestUpdate()
{
}

