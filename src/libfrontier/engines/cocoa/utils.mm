
#include "utils.h"

using namespace std;

@implementation CocoaUtils

+ (NSString*)wstringToNSString:(wstring)wstr
{
    return [[NSString alloc]
        initWithBytes: wstr.data()
        length: wstr.size() * sizeof(wchar_t)
        encoding: NSUTF32LittleEndianStringEncoding];
}

@end

