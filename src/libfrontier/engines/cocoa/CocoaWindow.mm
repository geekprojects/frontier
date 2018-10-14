
#include "cocoa_engine.h"
#include "utils.h"

#include <Cocoa/Cocoa.h>

using namespace std;
using namespace Frontier;

#include "keycode_map.h"

@interface CocoaNSWindow : NSWindow
{
    CocoaWindow* m_engineWindow;
}

- (void)setEngineWindow:(CocoaWindow*)cocoaWindow;
- (CocoaWindow*)getEngineWindow;

//- (void)setPosition: (unsigned int) x y:(unsigned int) y;

- (void)windowDidResize: (NSNotification *)notification; 

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

- (void)setPosition: (unsigned int) x y:(unsigned int) y
{
}

- (void)windowDidResize: (NSNotification *)notification 
{
    NSRect rect = [self contentRectForFrameRect:[self frame]];
    NSLog(@"CocoaNSWindow.windowDidResize: w=%0.2f, h=%0.2f", rect.size.width, rect.size.height);

    int w = rect.size.width;
    int h = rect.size.height;

    m_engineWindow->getWindow()->setSize(Frontier::Size(w, h));
    m_engineWindow->getWindow()->update();

    NSLog(@"CocoaNSWindow.windowDidResize: (screen) backingScaleFactor=%0.2f", [[self screen] backingScaleFactor]);
}

@end

@interface FrontierView : NSView
{
    CocoaWindow* m_engineWindow;
    CGImageRef m_image;

    NSTrackingArea* trackingArea;
}

- (void)setImage:(CGImageRef)image;
- (void)setEngineWindow:(CocoaWindow*)cocoaWindow;

- (void)updateTrackingAreas;

- (void)drawRect:(NSRect)dirtyRect;

- (void)mouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)scrollWheel:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)keyDown:(NSEvent *)theEvent;

- (Frontier::InputMessage*)createKeyMessage:(NSEvent*)event;

@end

@implementation FrontierView
- (void)drawRect:(NSRect)dirtyRect
{
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

- (void)updateTrackingAreas
{
#if 0
    if (trackingArea != NULL)
    {
        [self removeTrackingArea: trackingArea];
    }
    NSTrackingAreaOptions options =(NSTrackingActiveAlways | NSTrackingInVisibleRect |  NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved);
    trackingArea = [[NSTrackingArea alloc]
        initWithRect: [self bounds]
        options: options
        owner: self
         userInfo: nil];
    [self addTrackingArea: trackingArea];
#endif
}

- (void)mouseDown:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    NSPoint pos = [theEvent locationInWindow];
    //NSLog(@"Mouse was clicked: location: %0.2f, %0.2f\n", pos.x, pos.y);

    Frontier::InputMessage* msg = new Frontier::InputMessage();
    msg->messageType = FRONTIER_MSG_INPUT;
    msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_BUTTON;
    msg->event.button.direction = true;//(event.button.type == SDL_MOUSEBUTTONDOWN);
    msg->event.button.button = 0;//event.button.button;
    msg->event.button.doubleClick = false;//(event.button.clicks == 2);

    int height = [self frame].size.height;
    msg->event.button.x = (int)pos.x;
    msg->event.button.y = height - (int)pos.y;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);

}

- (void)mouseUp:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    NSPoint pos = [theEvent locationInWindow];
    //NSLog(@"Mouse was clicked: location: %0.2f, %0.2f\n", pos.x, pos.y);

    Frontier::InputMessage* msg = new Frontier::InputMessage();
    msg->messageType = FRONTIER_MSG_INPUT;
    msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_BUTTON;
    msg->event.button.direction = false;//(event.button.type == SDL_MOUSEBUTTONDOWN);
    msg->event.button.button = 0;//event.button.button;
    msg->event.button.doubleClick = false;//(event.button.clicks == 2);

int height = [self frame].size.height;
    msg->event.button.x = (int)pos.x;
    msg->event.button.y = height - (int)pos.y;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);

}

- (void)mouseMoved:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    NSPoint pos = [theEvent locationInWindow];
    //NSLog(@"Mouse was moved: location: %0.2f, %0.2f\n", pos.x, pos.y);

    Frontier::InputMessage* msg = new Frontier::InputMessage();
    msg->messageType = FRONTIER_MSG_INPUT;
    msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_MOTION;
    //msg->event.button.direction = false;//(event.button.type == SDL_MOUSEBUTTONDOWN);
    //msg->event.button.button = 0;//event.button.button;
    //msg->event.button.doubleClick = false;//(event.button.clicks == 2);

    int height = [self frame].size.height;
    msg->event.button.x = (int)pos.x;
    msg->event.button.y = height - (int)pos.y;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];

    NSPoint pos = [theEvent locationInWindow];
    //NSLog(@"Mouse was dragged: location: %0.2f, %0.2f\n", pos.x, pos.y);

    Frontier::InputMessage* msg = new Frontier::InputMessage();
    msg->messageType = FRONTIER_MSG_INPUT;
    msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_MOTION;
    //msg->event.button.direction = false;//(event.button.type == SDL_MOUSEBUTTONDOWN);
    //msg->event.button.button = 0;//event.button.button;
    //msg->event.button.doubleClick = false;//(event.button.clicks == 2);

    int height = [self frame].size.height;
    msg->event.button.x = (int)pos.x;
    msg->event.button.y = height - (int)pos.y;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);
}

- (void)scrollWheel:(NSEvent *)theEvent
{
    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
    NSPoint pos = [theEvent locationInWindow];
    NSLog(@"scrollWheel: location: %0.2f, %0.2f\n", pos.x, pos.y);
    bool hasPreciseScrollingDeltas = [theEvent hasPreciseScrollingDeltas];
    CGFloat scrollX = [theEvent scrollingDeltaX];
    CGFloat scrollY = [theEvent scrollingDeltaY];
    NSLog(@"scrollWheel: scroll: %0.2f, %0.2f  hasPreciseScrollingDeltas=%d\n", scrollX, scrollY, hasPreciseScrollingDeltas);

    Frontier::InputMessage* msg = new Frontier::InputMessage();
    msg->messageType = FRONTIER_MSG_INPUT;
    msg->inputMessageType = FRONTIER_MSG_INPUT_MOUSE_WHEEL;

    int height = [self frame].size.height;
    msg->event.wheel.x = (int)pos.x;
    msg->event.wheel.y = height - (int)pos.y;
    msg->event.wheel.scrollX = (int)scrollX;
    msg->event.wheel.scrollY = (int)scrollY;

    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);
}

- (void)keyUp:(NSEvent *)theEvent
{
    Frontier::InputMessage* msg = [self createKeyMessage: theEvent];
    msg->event.key.direction = false;

    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);
}

- (void)keyDown:(NSEvent *)theEvent
{
    Frontier::InputMessage* msg = [self createKeyMessage: theEvent];
    msg->event.key.direction = true;

    CocoaNSWindow* window = (CocoaNSWindow*)[theEvent window];
    CocoaWindow* cwindow = [window getEngineWindow];
    cwindow->getWindow()->handleMessage(msg);
}

- (Frontier::InputMessage*)createKeyMessage:(NSEvent*)theEvent
{
    uint16_t keyCode = [theEvent keyCode];
    NSString* chars = [theEvent characters];
    int modifierFlags = [theEvent modifierFlags];

    std::string wchars = std::string([chars UTF8String], [chars lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);

    char c = 0;
    if (wchars.length() > 0)
    {
        c = wchars.at(0);
    }

    if (c && isprint(c))
    {
        NSLog(@"createKeyMessage: keyCode=0x%x, chars=%c", keyCode, c);
    }
    else
    {
        NSLog(@"createKeyMessage: keyCode=0x%x", keyCode);
    }

    Frontier::InputMessage* msg = new Frontier::InputMessage();
    msg->messageType = FRONTIER_MSG_INPUT;
    msg->inputMessageType = FRONTIER_MSG_INPUT_KEY;

    if (wchars.length() > 0)
    {
        msg->event.key.chr = wchars.at(0);
    }

    if (keyCode < 128)
    {
        msg->event.key.key = g_darwinKeyCodeMap[keyCode];
    }
    else
    {
        msg->event.key.key = KC_UNKNOWN;
    }

    msg->event.key.modifiers = 0;
    if (modifierFlags & NSEventModifierFlagCapsLock)
    {
        msg->event.key.modifiers |= KMOD_CAPS_LOCK;
    }
    if (modifierFlags & NSEventModifierFlagShift)
    {
        msg->event.key.modifiers |= KMOD_SHIFT;
    }
    if (modifierFlags & NSEventModifierFlagControl)
    {
        msg->event.key.modifiers |= KMOD_CONTROL;
    }
    if (modifierFlags & NSEventModifierFlagOption)
    {
        msg->event.key.modifiers |= KMOD_ALT;
    }
    if (modifierFlags & NSEventModifierFlagCommand)
    {
        msg->event.key.modifiers |= KMOD_COMMAND;
    }

    return msg;
}

@end

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

    m_cocoaWindow = window;

    NSString* titleStr = [CocoaUtils wstringToNSString:m_window->getTitle()];
    [window setTitle: titleStr];

    NSRect rect = [window contentRectForFrameRect:[window frame]];
    rect.origin.x = 0;
    rect.origin.y = 0;
    FrontierView* view = [[FrontierView alloc] initWithFrame:rect];
    m_cocoaView = view;
    [[window contentView] addSubview: view];
    [window makeFirstResponder: view];

    //[window makeKeyAndOrderFront:nil];

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
    point.y = (screenFrame.size.height - y) - rect.size.height;
    [window setFrameTopLeftPoint: point];
}

Geek::Vector2D CocoaWindow::getPosition()
{
    CocoaNSWindow* window = (CocoaNSWindow*)m_cocoaWindow;

    NSScreen* screen = [window screen];
    NSRect screenFrame = [screen frame];
    printf("CocoaWindow.getPosition: screen size: %d, %d\n", (int)screenFrame.size.width, (int)screenFrame.size.height);

    NSRect rect = [window frame];
    printf("CocoaWindow.getPosition: window origin: %d, %d\n", (int)rect.origin.x, (int)rect.origin.y);
    Geek::Vector2D pos;
    pos.x = rect.origin.x;
    pos.y = (int)(screenFrame.size.height - (rect.origin.y + rect.size.height));
    printf("CocoaWindow.getPosition: %u, %u\n", pos.x, pos.y);
    return pos;
}

