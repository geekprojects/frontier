#ifndef __FRONTIER_ENGINE_COCOA_UTILS_H_
#define __FRONTIER_ENGINE_COCOA_UTILS_H_

#include <Cocoa/Cocoa.h>
#include <string>

@interface CocoaUtils : NSObject
{
}

+ (NSString*)wstringToNSString:(std::wstring)wstr;

@end


#endif
