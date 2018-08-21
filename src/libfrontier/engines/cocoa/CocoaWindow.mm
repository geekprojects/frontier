
#include "cocoa_engine.h"

#include <Cocoa/Cocoa.h>

@interface CocoaNSWindow : NSWindow
{
    CocoaWindow* m_engineWindow;
}

- (void)setEngineWindow:(CocoaWindow*)cocoaWindow;
- (CocoaWindow*)getEngineWindow;

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

- (void)windowDidResize: (NSNotification *)notification 
{
    NSRect rect = [self contentRectForFrameRect:[self frame]];
    NSLog(@"CocoaNSWindow.windowDidResize: w=%0.2f, h=%0.2f", rect.size.width, rect.size.height);

int w = rect.size.width;
int h = rect.size.height;

m_engineWindow->getWindow()->setSize(Frontier::Size(w, h));
m_engineWindow->getWindow()->update();
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

@end

@implementation FrontierView
- (void)drawRect:(NSRect)dirtyRect
{
    printf("drawRect: m_image=%p\n", m_image);
    if (m_image != NULL)
    {
        CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext]     graphicsPort];
        if (context==nil) {
            NSLog(@"context failed");
            return;
        }

        int width = [self frame].size.width;
        int height = [self frame].size.height;
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
    NSLog(@"Mouse was clicked: window=%p", window);

    NSPoint pos = [theEvent locationInWindow];
    NSLog(@"Mouse was clicked: location: %0.2f, %0.2f\n", pos.x, pos.y);

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
    NSLog(@"Mouse was clicked: window=%p", window);

    NSPoint pos = [theEvent locationInWindow];
    NSLog(@"Mouse was clicked: location: %0.2f, %0.2f\n", pos.x, pos.y);

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
    NSLog(@"Mouse was moved: window=%p", window);

    NSPoint pos = [theEvent locationInWindow];
    NSLog(@"Mouse was moved: location: %0.2f, %0.2f\n", pos.x, pos.y);

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
    NSLog(@"Mouse was dragged: window=%p", window);

    NSPoint pos = [theEvent locationInWindow];
    NSLog(@"Mouse was dragged: location: %0.2f, %0.2f\n", pos.x, pos.y);

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

@end

bool CocoaWindow::createCocoaWindow()
{
    CocoaNSWindow* window;
    window = [[CocoaNSWindow alloc]
        initWithContentRect: NSMakeRect(0, 0, 200, 200)
        styleMask: NSWindowStyleMaskTitled | NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
        backing: NSBackingStoreBuffered
        defer: NO];

    [window setAcceptsMouseMovedEvents:YES];

    [window setEngineWindow: this];

    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    [nc addObserver:window selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:window];

    m_cocoaWindow = window;
    [window setTitle: @"Test window"];

    NSRect rect = [window contentRectForFrameRect:[window frame]];
    rect.origin.x = 0;
    rect.origin.y = 0;
    FrontierView* view = [[FrontierView alloc] initWithFrame:rect];
    m_cocoaView = view;
    [[window contentView] addSubview: view];

    [window makeKeyAndOrderFront:nil];

    return true;
}

Frontier::Size CocoaWindow::getSize()
{
/*
    NSRect rect = [m_cocoaWindow contentRectForFrameRect:[m_cocoaWindow frame]];

    return Frontier::Size(rect.size.width, rect.size.height);
*/
    return Frontier::Size(0, 0);
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
    [m_cocoaView setFrameSize: nssize];
}

bool CocoaWindow::drawSurface(Geek::Gfx::Surface* surface)
{

    int width = surface->getWidth();
    int height = surface->getHeight();

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
        kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast,
        provider,
        NULL,
        true,
        kCGRenderingIntentDefault);

    [m_cocoaView setImage: image];
    [m_cocoaView setNeedsDisplay:YES];

    //Clean up
    CGColorSpaceRelease(colorspace);
    CGDataProviderRelease(provider);

    return true;
}

