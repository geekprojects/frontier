
#include "cocoa_engine.h"

#include <Cocoa/Cocoa.h>

bool CocoaEngine::createApplication()
{
    m_application = [NSApplication sharedApplication];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    return true;
}

bool CocoaEngine::run()
{
    [m_application run];

    return false;
}


