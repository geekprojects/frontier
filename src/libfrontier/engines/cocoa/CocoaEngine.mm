
#include "CocoaEngine.h"
#include "CocoaWindow.h"
#include "utils.h"

#include <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

@interface MenuTarget : NSObject
{
}

- (void)onMenuItem:(id)sender;

@end

@implementation MenuTarget
- (void)onMenuItem:(id)sender
{
    MenuItem* menuItem = (MenuItem*)[(NSValue*)[sender representedObject] pointerValue];
    if (menuItem != NULL)
    {
        menuItem->clickSignal().emit(menuItem);
    }
}

@end

@interface FrontierAppDelegate : NSObject <NSApplicationDelegate>

- (id)init;

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;

@end

@implementation FrontierAppDelegate : NSObject
- (id)init
{
    self = [super init];

    return self;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    [NSApp stop:self];
    printf("FrontierAppDelegate::applicationShouldTerminate: Here!\n");
    return NSTerminateCancel;
}
@end


CocoaEngine::CocoaEngine(FrontierApp* app) : FrontierEngine(app)
{
    m_currentMenu = (Menu*)-1;
    m_windowMenu = NULL;
}

CocoaEngine::~CocoaEngine()
{
}

bool CocoaEngine::init()
{
    bool res;

    res = createApplication();
    if (!res)
    {
        return false;
    }

    return true;
}

bool CocoaEngine::initWindow(FrontierWindow* window)
{

    bool res;

    CocoaWindow* cw = new CocoaWindow(this, window);

    res = cw->init();
    if (!res)
    {
        return false;
    }

    window->setEngineWindow(cw);
    return true;
}

bool CocoaEngine::checkEvents()
{
    return run();
}

bool CocoaEngine::quit()
{
    NSApplication* app = (NSApplication*)m_application;

    [app terminate:nil];

    return true;
}

bool CocoaEngine::createApplication()
{
    m_application = [NSApplication sharedApplication];

    FrontierAppDelegate* appDelegate = [[FrontierAppDelegate alloc] init];
    m_appDelegate = appDelegate;
    [NSApp setDelegate:appDelegate];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];


    log(DEBUG, "createApplication: Creating Window menu...");
    NSMenu* windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
    [NSApp setWindowsMenu:windowMenu];

    /* Add menu items */
    [windowMenu addItemWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [windowMenu addItemWithTitle:@"Zoom" action:@selector(performZoom:) keyEquivalent:@""];

    /* Put menu into the menubar */
    NSMenuItem* windowMenuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [windowMenuItem setSubmenu:windowMenu];
    m_windowMenu = windowMenuItem;

    updateMenu(m_app->getAppMenu());

    m_app->activeWindowChangedSignal().connect(sigc::mem_fun(*this, &CocoaEngine::onActiveWindowChanged));

    return true;
}

void CocoaEngine::updateMenu(Menu* frontierMenu)
{
    if (m_currentMenu == frontierMenu)
    {
        return;
    }

    [[NSApp mainMenu] removeItem:(NSMenuItem*)m_windowMenu];

    m_currentMenu = frontierMenu;
    printf("CocoaEngine::updateMenu: Updating menu: %p", frontierMenu);

    // Create NSMenu
    NSMenu* mainMenu = [[NSMenu alloc] init];


    if (frontierMenu != NULL && !frontierMenu->getMenuItems().empty())
    {
        MenuItem* firstItem = frontierMenu->getMenuItems().at(0);
        if (firstItem->getTitle() != L"__APP__")
        {
            addAppMenu(mainMenu);
        }

        MenuTarget* target = [MenuTarget alloc];
        for (MenuItem* menu : frontierMenu->getMenuItems())
        {
            log(DEBUG, "updateMenu: Menu: %ls", menu->getTitle().c_str());
            NSString* titleStr = [CocoaUtils wstringToNSString:menu->getTitle()];

            NSMenu* nsmenu = [[NSMenu alloc] initWithTitle:titleStr];

            for (MenuItem* child : menu->getChildren())
            {
                if (!child->getIsSeparator())
                {
                    NSString* childTitleStr = [CocoaUtils wstringToNSString:child->getTitle()];
                    NSMenuItem* childItem = [nsmenu addItemWithTitle:childTitleStr action:@selector(onMenuItem:) keyEquivalent:@""];
                    childItem.representedObject = [NSValue valueWithPointer:child];
                    if (child->getKey() != 0)
                    {
                        unichar c[2];
                        c[0] = child->getKey();
                        c[1] = 0;
                        childItem.keyEquivalent = [[NSString alloc] initWithCharacters:c length:1];
                    }
                    childItem.target = target;
                }
                else
                {
                    [nsmenu addItem:[NSMenuItem separatorItem]];
                }
            }

            NSMenuItem* menuItem = [[NSMenuItem alloc] initWithTitle:titleStr action:nil keyEquivalent:@""];
            [menuItem setSubmenu:nsmenu];
            [mainMenu addItem:menuItem];
        }
    }
    else
    {
        addAppMenu(mainMenu);
    }

    log(DEBUG, "updateMenu: Adding Window menu");
    [mainMenu addItem:(NSMenuItem*)m_windowMenu];

    log(DEBUG, "updateMenu: Setting main menu...");
    [NSApp setMainMenu:mainMenu];

    [mainMenu release];  /* we're done with it, let NSApp own it. */
    log(DEBUG, "updateMenu: Done!");
}

void CocoaEngine::addAppMenu(void* menuPtr)
{
    NSMenu* mainMenu = (NSMenu*)menuPtr;

    NSString* appName = [[NSProcessInfo processInfo] processName];

    // Main app menu
    NSMenu* appleMenu = [[NSMenu alloc] initWithTitle:@""];

    NSString* quitTitle = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:quitTitle action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];

    [appleMenu addItem:[NSMenuItem separatorItem]];

    NSString* title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];

    /* Put app menu into the menubar */
    NSMenuItem* menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [mainMenu addItem:menuItem];
    [menuItem release];
}


bool CocoaEngine::run()
{
    log(INFO, "run: Starting run");
    NSApplication* app = (NSApplication*)m_application;
    [app run];

    log(INFO, "run: run has exited");

    return false;
}

void CocoaEngine::onActiveWindowChanged(FrontierWindow* window)
{
    printf("CocoaEngine::onActiveWindowChanged: window=%p\n", window);
    Menu* menu = NULL;
    if (window != NULL)
    {
        printf("CocoaEngine::onActiveWindowChanged: window title: %ls\n", window->getTitle().c_str());
        menu = window->getMenu();
        printf("CocoaEngine::onActiveWindowChanged: window menu=%p\n", menu);
    }
    if (menu == NULL)
    {
        menu = m_app->getAppMenu();
        printf("CocoaEngine::onActiveWindowChanged: using app menu=%p\n", menu);
    }
    updateMenu(menu);
}

void CocoaEngine::message(string title, string message)
{
}

bool CocoaEngine::confirmBox(string title, string message)
{
#if 0
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:@"Delete this project?"];
    [alert setInformativeText:@"Deleted projects cannot be restored"];
    [alert addButtonWithTitle:@"OK"];
    [alert addButtonWithTitle:@"Cancel"];
    [alert setAlertStyle:NSWarningAlertStyle];

    [alert beginSheetModalForWindow:nil completionHandler:^(NSModalResponse returnCode)
    {
        if (returnCode == NSAlertSecondButtonReturn)
        {
            NSLog(@"Delete was cancelled!");
            return false;
        }
    
        NSLog(@"This project was deleted!");
        return true;
    }];
#endif
return false;
}

std::string CocoaEngine::chooseFile(int flags, string path, string pattern)
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];

    // Enable the selection of files in the dialog.
if (!(flags & DIRECTORIES_ONLY))
{
    [openDlg setCanChooseFiles:YES];
}
else
{
    [openDlg setCanChooseFiles:NO];
}

    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:YES];

    // Display the dialog.  If the OK button was pressed process the files.
    bool res = [openDlg runModalForDirectory:nil file:nil];
    if (res)
    {
        NSString* filename = [openDlg filename];
        return std::string([filename UTF8String], [filename lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
    }

    return "";
}

ColourPickerWindow* CocoaEngine::openColourPickerWindow(Geek::Gfx::Colour colour)
{
    return new CocoaColourPickerWindow(colour);
}

string CocoaEngine::getConfigDir()
{
    NSError *error;
    NSURL *appSupportDir = [[NSFileManager defaultManager] URLForDirectory:NSApplicationSupportDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:YES error:&error];

    NSString* path = [appSupportDir path];

    return std::string([path UTF8String], [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding]) + "/" + Utils::wstring2string(m_app->getName());
}


@interface ColourTarget : NSObject
{
    CocoaColourPickerWindow* m_window;
}

- (void)setWindow:(CocoaColourPickerWindow*)cocoaWindow;
- (void)colourAction:(id)sender;

@end

@implementation ColourTarget

- (void)setWindow:(CocoaColourPickerWindow*)window
{
    m_window = window;
}

- (void)colourAction:(id)sender
{
    float r = [[sender color] redComponent];
    float g = [[sender color] greenComponent];
    float b = [[sender color] blueComponent];
    float a = [[sender color] alphaComponent];
    Colour colour(a * 255.0, r * 255.0, g * 255.0, b * 255.0);
    printf("ColourTarget::colourAction: r=%0.2f, g=%0.2f, b=%0.2f, a=%0.2f: %s\n", r, g, b, a, colour.toHexString().c_str());

    m_window->colourSelectedSignal().emit(colour);
}

@end

CocoaColourPickerWindow::CocoaColourPickerWindow(Colour colour) : ColourPickerWindow(colour)
{
    NSColorPanel *cpanel = [NSColorPanel sharedColorPanel];
NSColor* nscolor = [NSColor colorWithSRGBRed:((float)colour.r / 255.0) green:((float)colour.g / 255.0) blue:((float)colour.b / 255.0) alpha:((float)colour.alpha / 255.0)];
    //[cpanel color:nscolor];
    cpanel.color = nscolor;

    ColourTarget* target = [ColourTarget alloc];
[target setWindow:this];
    [cpanel setAction:@selector(colourAction:)];
    [cpanel setTarget:target];
    [cpanel makeKeyAndOrderFront:nil];
}

CocoaColourPickerWindow::~CocoaColourPickerWindow()
{
}

