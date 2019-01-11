
#include "cocoa_engine.h"
#include "utils.h"

#include <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>

using namespace std;
using namespace Frontier;
using namespace Geek;

@interface MenuTarget : NSObject
{
    CocoaEngine* m_engine;
}

- (void)setCocoaEngine:(CocoaEngine*) engine;
- (void)onMenuItem;

@end

@implementation MenuTarget
- (void)setCocoaEngine:(CocoaEngine*) engine
{
    m_engine = engine;
}

- (void)onMenuItem
{
    printf("MenuTarget.menuItemAction: Here!\n");
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

bool CocoaEngine::createApplication()
{
    m_application = [NSApplication sharedApplication];

    FrontierAppDelegate* appDelegate = [[FrontierAppDelegate alloc] init];
    m_appDelegate = appDelegate;

    [NSApp setDelegate:appDelegate];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSString* appName = [[NSProcessInfo processInfo] processName];

    NSMenu* mainMenu = [[NSMenu alloc] init];
    [NSApp setMainMenu:mainMenu];

    [mainMenu release];  /* we're done with it, let NSApp own it. */
    mainMenu = nil;

    NSMenu* appleMenu = [[NSMenu alloc] initWithTitle:@""];

    NSString* quitTitle = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:quitTitle action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];

    [appleMenu addItem:[NSMenuItem separatorItem]];

    NSString* title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];

    /* Put menu into the menubar */
    NSMenuItem* menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [[NSApp mainMenu] addItem:menuItem];
    [menuItem release];

MenuTarget* target = [MenuTarget alloc];

    vector<MenuItem*>* appMenu = m_app->getAppMenu();
    for (MenuItem* menu : *appMenu)
    {
        log(DEBUG, "createApplication: Menu: %ls", menu->getTitle().c_str());
        NSString* titleStr = [CocoaUtils wstringToNSString:menu->getTitle()];

        NSMenu* nsmenu = [[NSMenu alloc] initWithTitle:titleStr];

        for (MenuItem* child : menu->getChildren())
        {
            NSString* childTitleStr = [CocoaUtils wstringToNSString:child->getTitle()];
            NSMenuItem* childItem = [nsmenu addItemWithTitle:childTitleStr action:@selector(target:onMenuItem:) keyEquivalent:@""];
childItem.target = target;

        }

        menuItem = [[NSMenuItem alloc] initWithTitle:titleStr action:nil keyEquivalent:@""];
        [menuItem setSubmenu:nsmenu];
        [[NSApp mainMenu] addItem:menuItem];
    }

    /* Create the window menu */
    NSMenu* windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];

    /* Add menu items */
    [windowMenu addItemWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];

    [windowMenu addItemWithTitle:@"Zoom" action:@selector(performZoom:) keyEquivalent:@""];

    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:windowMenu];
    [[NSApp mainMenu] addItem:menuItem];
    [menuItem release];

    return true;
}

bool CocoaEngine::run()
{
    log(INFO, "run: Starting run");
    NSApplication* app = (NSApplication*)m_application;
    [app run];

    log(INFO, "run: run has exited");

    return false;
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

bool CocoaEngine::onMenuItem(MenuItem* item)
{
    log(DEBUG, "onMenuItem: item=%p", item);
    return true;
}

string CocoaEngine::getConfigDir()
{
    NSError *error;
    NSURL *appSupportDir = [[NSFileManager defaultManager] URLForDirectory:NSApplicationSupportDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:YES error:&error];

    NSString* path = [appSupportDir path];

    return std::string([path UTF8String], [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding]) + "/" + Utils::wstring2string(m_app->getName());
}

