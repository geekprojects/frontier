
#include "CocoaWindow.h"
#include "CocoaEngine.h"
#include "utils.h"

#include <Cocoa/Cocoa.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

#include "keycode_map.h"

@interface CocoaNSWindow : NSWindow
{
    CocoaWindow* m_engineWindow;
}

- (void)setEngineWindow:(CocoaWindow*)cocoaWindow;
- (CocoaWindow*)getEngineWindow;

- (BOOL)windowShouldClose:(id) sender;
- (void)windowDidResize: (NSNotification *)notification; 
- (void)windowDidBecomeKey: (NSNotification *)notification; 
- (void)windowDidResignKey: (NSNotification *)notification; 

@end

@implementation CocoaNSWindow

- (void)setEngineWindow:(CocoaWindow*)cocoaWindow
{
    m_engineWindow = cocoaWindow;
}

- (CocoaWindow*)getEngineWindow;
{
    return m_engineWindow;
}

-(BOOL) windowShouldClose:(id) sender
{
    m_engineWindow->getWindow()->closeSignal().emit();
    return NO;
}

- (void)windowDidResize: (NSNotification *)notification 
{
    NSRect rect = [self contentRectForFrameRect:[self frame]];

    int w = rect.size.width;
    int h = rect.size.height;

    m_engineWindow->getWindow()->setSize(Frontier::Size(w, h));
    m_engineWindow->getWindow()->update();
}

- (void)windowDidBecomeKey: (NSNotification *)notification
{
    printf("windowDidBecomeKey: this=%p\n", self);
    FrontierWindow* frnwin = m_engineWindow->getWindow();
    frnwin->getApp()->setActiveWindow(frnwin);
}

- (void)windowDidResignKey: (NSNotification *)notification
{
printf("windowDidResignKey: this=%p\n", self);
}

@end

@interface FrontierView : NSView
{
    CocoaWindow* m_engineWindow;
    CGImageRef m_image;
    NSCursor* m_cursor;
}

- (void)setImage:(CGImageRef)image;
- (void)setEngineWindow:(CocoaWindow*)cocoaWindow;

- (void)drawRect:(NSRect)dirtyRect;

- (void)mouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)touchesBeganWithEvent:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;

- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;

- (void)scrollWheel:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)keyDown:(NSEvent *)theEvent;

- (Frontier::KeyEvent*)createKeyEvent:(NSEvent*)event;
- (Frontier::MouseButtonEvent*)createMouseButtonEvent:(NSEvent*)event;

- (void)setCursor:(NSCursor*)cursor;
- (void)resetCursorRects;

@end

@implementation FrontierView
- (void)drawRect:(NSRect)dirtyRect
{
    NSAssert( [NSThread isMainThread], @"This needs to run in the main thread" );

    if (m_image != NULL)
    {
        CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext]     graphicsPort];
        if (context==nil) {
            NSLog(@"context failed");
            return;
        }

        float width = [self frame].size.width;// / 2;
        float height = [self frame].size.height;// / 2;
        CGRect renderRect = CGRectMake(0., 0., width, height);

        CGContextDrawImage(context, renderRect, m_image);
    }
}

- (void)setImage:(CGImageRef)image
{
    if (m_image != NULL)
    {
        CGImageRelease(m_image);
    }
    m_image = image;
}

- (void)setEngineWindow:(CocoaWindow*)cocoaWindow
{
    m_engineWindow = cocoaWindow;

}

- (void)mouseDown:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    Frontier::MouseButtonEvent* event = [self createMouseButtonEvent: theEvent];
    event->direction = true;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);

}

- (void)mouseUp:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    Frontier::MouseButtonEvent* event = [self createMouseButtonEvent: theEvent];
    event->direction = false;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);
}

- (void)touchesBeganWithEvent:(NSEvent *)theEvent
{
    NSSet *touches = [theEvent touchesMatchingPhase:NSTouchPhaseTouching inView:self];
    int count = [touches count];
    if (count == 2)
    {
        printf("touchesBeganWithEvent: TWO FINGERS\n");
        Frontier::MouseButtonEvent* event = [self createMouseButtonEvent: theEvent];
        event->direction = false;

        CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
        CocoaWindow* cwindow = [window getEngineWindow];
        cwindow->getWindow()->handleEvent(event);
    }
}

- (Frontier::MouseButtonEvent*)createMouseButtonEvent:(NSEvent*)theEvent
{
    NSPoint pos = [theEvent locationInWindow];

    int button;
    int type = [theEvent type];
    int clickCount = 1;
    if (type == NSEventTypeGesture)
    {
        button = BUTTON_RIGHT;
    }
    else
    {
        clickCount = [theEvent clickCount];

        if (([theEvent modifierFlags] & NSEventModifierFlagControl))
        {
            button = BUTTON_RIGHT;
        }
        else
        {
            button = BUTTON_LEFT;
        }
    }

    Frontier::MouseButtonEvent* event = new Frontier::MouseButtonEvent();
    event->eventType = FRONTIER_EVENT_MOUSE_BUTTON;
    event->buttons = button;
    event->doubleClick = clickCount == 2;

    int height = [self frame].size.height;
    event->x = (int)pos.x;
    event->y = height - (int)pos.y;

    return event;
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    NSPoint pos = [theEvent locationInWindow];

    Frontier::MouseMotionEvent* event = new Frontier::MouseMotionEvent();
    event->eventType = FRONTIER_EVENT_MOUSE_MOTION;

    int height = [self frame].size.height;
    event->x = (int)pos.x;
    event->y = height - (int)pos.y;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    NSPoint pos = [theEvent locationInWindow];

    Frontier::MouseMotionEvent* event = new Frontier::MouseMotionEvent();
    event->eventType = FRONTIER_EVENT_MOUSE_MOTION;

    int height = [self frame].size.height;
    event->x = (int)pos.x;
    event->y = height - (int)pos.y;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    printf("mouseEntered: Here!\n");
}

- (void)mouseExited:(NSEvent *)theEvent
{
    printf("mouseExited: Here!\n");
}


- (void)scrollWheel:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
    NSPoint pos = [theEvent locationInWindow];

    CGFloat scrollX = [theEvent scrollingDeltaX];
    CGFloat scrollY = [theEvent scrollingDeltaY];

#if 0
    bool hasPreciseScrollingDeltas = [theEvent hasPreciseScrollingDeltas];
    NSLog(@"scrollWheel: scroll: %0.2f, %0.2f  hasPreciseScrollingDeltas=%d\n", scrollX, scrollY, hasPreciseScrollingDeltas);
#endif

    Frontier::MouseScrollEvent* event = new Frontier::MouseScrollEvent();
    event->eventType = FRONTIER_EVENT_MOUSE_SCROLL;

    int height = [self frame].size.height;
    event->x = (int)pos.x;
    event->y = height - (int)pos.y;
    event->scrollX = (int)scrollX;
    event->scrollY = (int)scrollY;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);
}

- (void)keyUp:(NSEvent *)theEvent
{
    Frontier::KeyEvent* event = [self createKeyEvent: theEvent];
    event->direction = false;

    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);
}

- (void)keyDown:(NSEvent *)theEvent
{
    Frontier::KeyEvent* event = [self createKeyEvent: theEvent];
    event->direction = true;

    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleEvent(event);
}

- (Frontier::KeyEvent*)createKeyEvent:(NSEvent*)theEvent
{
    uint16_t keyCode = [theEvent keyCode];
    NSString* chars = [theEvent characters];
    int modifierFlags = [theEvent modifierFlags];

    std::string wchars = std::string([chars UTF8String], [chars lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);

    Frontier::KeyEvent* event = new Frontier::KeyEvent();
    event->eventType = FRONTIER_EVENT_KEY;

    if (wchars.length() > 0)
    {
        event->key = wchars.at(0);
    }

    unsigned int c = 0;
    if (wchars.length() > 0)
    {
        c = wchars.at(0);
    }
    event->chr = c;

    if (wchars.length() > 0 && c != 0xffffffef && !iscntrl(c))
    {
        if (isprint(c))
        {
            NSLog(@"createKeyMessage: keyCode=0x%x, chars=%c", keyCode, c);
        }
        else
        {
            NSLog(@"createKeyMessage: keyCode=0x%x, chars=0x%x", keyCode, c);
        }

        event->key = toupper(c);
    }
    else if (keyCode < 128)
    {
        event->key = g_darwinKeyCodeMap[keyCode];
    }
    else
    {
        event->key = KC_UNKNOWN;
    }

    event->modifiers = 0;
    if (modifierFlags & NSEventModifierFlagCapsLock)
    {
        event->modifiers |= KMOD_CAPS_LOCK;
    }
    if (modifierFlags & NSEventModifierFlagShift)
    {
        event->modifiers |= KMOD_SHIFT;
    }
    if (modifierFlags & NSEventModifierFlagControl)
    {
        event->modifiers |= KMOD_CONTROL;
    }
    if (modifierFlags & NSEventModifierFlagOption)
    {
        event->modifiers |= KMOD_ALT;
    }
    if (modifierFlags & NSEventModifierFlagCommand)
    {
        event->modifiers |= KMOD_COMMAND;
    }

    return event;
}

- (void)setCursor:(NSCursor*)cursor
{
    m_cursor = cursor;
}

- (void)resetCursorRects
{
    if (m_cursor != NULL)
    {
        [self addCursorRect:[self bounds] cursor:m_cursor];
    }
}

@end

CocoaWindow::CocoaWindow(FrontierEngine* engine, FrontierWindow* window) : FrontierEngineWindow(engine, window)
{
}

CocoaWindow::~CocoaWindow()
{
}


bool CocoaWindow::init()
{
    return createCocoaWindow();
}

bool CocoaWindow::update()
{
    Size winSize = m_window->getSize();
    //setSize(winSize);

#if 1
    Size currentSize = getSize();
    if (currentSize.width != winSize.width || currentSize.height != winSize.height)
    {
        setSize(winSize);
    }
#endif

    drawSurface(m_window->getSurface());

    return true;
}

bool CocoaWindow::createCocoaWindow()
{
    CocoaNSWindow* window;

    int styleMask = 0;
    if (m_window->hasBorder())
    {
        styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable;
    }
    else
    {
        styleMask = NSWindowStyleMaskBorderless;
    }

    if (m_window->isResizeable())
    {
        styleMask |= NSWindowStyleMaskResizable;
    }

    window = [[CocoaNSWindow alloc]
        initWithContentRect: NSMakeRect(0, 0, 200, 200)
        styleMask: styleMask
        backing: NSBackingStoreBuffered
        defer: YES];

    [window setAcceptsMouseMovedEvents:YES];

    [window setEngineWindow: this];

    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    [nc addObserver:window selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:window];
    [nc addObserver:window selector:@selector(windowDidBecomeKey:) name:NSWindowDidBecomeKeyNotification object:window];
    [nc addObserver:window selector:@selector(windowDidResignKey:) name:NSWindowDidResignKeyNotification object:window];

    m_cocoaWindow = window;

    NSString* titleStr = [CocoaUtils wstringToNSString:m_window->getTitle()];
    [window setTitle: titleStr];

    NSRect rect = [window contentRectForFrameRect:[window frame]];
    rect.origin.x = 0;
    rect.origin.y = 0;

    FrontierView* view = [[FrontierView alloc] initWithFrame:rect];
    [view setAcceptsTouchEvents:YES];
    m_cocoaView = view;
    [[window contentView] addSubview: view];
    [window makeFirstResponder: view];

    NSTrackingArea* trackingArea = [[NSTrackingArea alloc]
        initWithRect:[view bounds]
        options: (NSTrackingMouseMoved | NSTrackingActiveAlways)
        owner:window
        userInfo:nil];
    [view addTrackingArea:trackingArea];


    // Capture any ApplicationDefined events. These are used to signal a redraw
    NSEvent *(^monitor)(NSEvent *event) = ^NSEvent *(NSEvent *event)
    {
        CocoaNSWindow* window = (CocoaNSWindow*)[event window];
        CocoaWindow* cwindow = [window getEngineWindow];
        cwindow->getWindow()->update();
        return event;
    };

    [NSEvent addLocalMonitorForEventsMatchingMask:NSApplicationDefinedMask handler:monitor];

    [window center];

    return true;
}

void CocoaWindow::show()
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    if (![window isMiniaturized])
    {
        [window makeKeyAndOrderFront:nil];
    }
}

void CocoaWindow::hide()
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    [window orderOut:nil];
}

Frontier::Size CocoaWindow::getSize()
{
#if 0
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    NSRect rect = [window contentRectForFrameRect:[window frame]];
    printf("CocoaWindow::getSize: %d, %d\n", (int)rect.size.width, (int)rect.size.height);
    return Frontier::Size(rect.size.width, rect.size.height);
#else
    return Frontier::Size(0, 0);
#endif
}

void CocoaWindow::setSize(Frontier::Size size)
{
    //Size size
    NSSize nssize;
    nssize.width = size.width;
    nssize.height = size.height;
    [(NSWindow*)m_cocoaWindow setContentSize : nssize];

    NSRect rect;
    rect.origin.x = 0;
    rect.origin.y = 0;
    rect.size = nssize;
    [(FrontierView*)m_cocoaView setFrameSize: nssize];
}

bool CocoaWindow::drawSurface(Geek::Gfx::Surface* surface)
{
    int width = surface->getWidth();
    int height = surface->getHeight();

#if 0
    printf("CocoaWindow::drawSurface: width=%d, height=%d, highDPI=%d\n", width, height, surface->isHighDPI());
#endif

    int len = width * height * 4;

    // Create a CGImage with the pixel data
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, surface->getData(), len, NULL);
    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    CGImageRef image = CGImageCreate(
        width,
        height,
        8,
        32,
        width * 4,
        colorspace,
        kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host,
        provider,
        NULL,
        true,
        kCGRenderingIntentDefault);

    FrontierView* view = (FrontierView*)m_cocoaView;
    [view setImage: image];

    // Tell Cocoa to redraw the window
    [view setNeedsDisplay:YES];

    //Clean up
    CGColorSpaceRelease(colorspace);
    CGDataProviderRelease(provider);

    return true;
}

float CocoaWindow::getScaleFactor()
{
    return [[(NSWindow*)m_cocoaWindow screen] backingScaleFactor];
}

void CocoaWindow::setPosition(unsigned int x, unsigned int y)
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    NSRect rect = [window frame];

    NSScreen* screen = [window screen];
    NSRect screenFrame = [screen frame];

    NSPoint point;
    point.x = x;
    point.y = screenFrame.size.height - (y + (rect.size.height / 2));

#if 0
    printf("CocoaWindow::setPosition: y=%d, screen height=%d, window height=%d -> %d\n", (int)y, (int)screenFrame.size.height, (int)rect.size.height, (int)point.y);
#endif

    [window setFrameTopLeftPoint: point];
}

Geek::Vector2D CocoaWindow::getPosition()
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;

    NSScreen* screen = [window screen];
    NSRect screenFrame = [screen frame];
    NSRect rect = [window frame];

    Geek::Vector2D pos;
    pos.x = rect.origin.x;
    pos.y = (int)(screenFrame.size.height - (rect.origin.y + rect.size.height));

#if 0
    printf(
        "CocoaWindow::getPosition: screenFrame.size.height=%d, rect.origin.y=%d, rect.size.height=%d, pos.y=%d\n",
        (int)screenFrame.size.height,
        (int)rect.origin.y,
        (int)rect.size.height,
        pos.y);
#endif

    return pos;
}

void CocoaWindow::resetCursor()
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    FrontierView* view = (FrontierView*)m_cocoaView;

    [view setCursor:NSCursor.arrowCursor];
    [window invalidateCursorRectsForView:view];
}

void CocoaWindow::updateCursor(WindowCursor cursor, int x, int y, int w, int h)
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    FrontierView* view = (FrontierView*)m_cocoaView;
    
    NSRect rect;
    rect.origin.x = x;
    rect.origin.y = y;
    rect.size.width = w;
    rect.size.height = h;

    NSCursor* nscursor = NULL;;

    switch (cursor)
    {
        case CURSOR_POINTER:
            nscursor = NSCursor.arrowCursor;
            break;
        case CURSOR_EDIT:
            nscursor = NSCursor.IBeamCursor;
            break;
        case CURSOR_RESIZE_HORIZONTAL:
            nscursor = NSCursor.resizeLeftRightCursor;
            break;
        case CURSOR_RESIZE_VERTICAL:
            nscursor = NSCursor.resizeUpDownCursor;
            break;
    }

    [view setCursor:nscursor];

    [window invalidateCursorRectsForView:view];
}

void CocoaWindow::requestUpdate()
{
    // Insert an ApplicationDefined event in to the event loop
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;
    NSEvent* event =[NSEvent otherEventWithType:NSEventTypeApplicationDefined
        location: NSZeroPoint
        modifierFlags: 0
        timestamp: 0
        windowNumber: [window windowNumber]
        context: nil
        subtype: 0
        data1: 0
        data2: 0];

    [NSApp postEvent:event atStart:NO];
}

