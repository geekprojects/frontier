
#include "CocoaEngine.h"
#include "CocoaWindow.h"
#include "utils.h"

#include <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

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

    if (frontierMenu != NULL)
    {
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

            menuItem = [[NSMenuItem alloc] initWithTitle:titleStr action:nil keyEquivalent:@""];
            [menuItem setSubmenu:nsmenu];
            [mainMenu addItem:menuItem];
        }
    }

    log(DEBUG, "updateMenu: Adding Window menu");
    [mainMenu addItem:(NSMenuItem*)m_windowMenu];

    log(DEBUG, "updateMenu: Setting main menu...");
    [NSApp setMainMenu:mainMenu];

    [mainMenu release];  /* we're done with it, let NSApp own it. */
    log(DEBUG, "updateMenu: Done!");
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

string CocoaEngine::getConfigDir()
{
    NSError *error;
    NSURL *appSupportDir = [[NSFileManager defaultManager] URLForDirectory:NSApplicationSupportDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:YES error:&error];

    NSString* path = [appSupportDir path];

    return std::string([path UTF8String], [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding]) + "/" + Utils::wstring2string(m_app->getName());
}

