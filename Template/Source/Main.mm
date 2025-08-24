#include "Main.h"

#include <thread>
#include <string>
#include <vector>
#include <cctype>
#include <mach-o/dyld.h>
#include <mach/mach.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/getsect.h>

#include <cstdio>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <arm_neon.h>
#include <sys/mman.h>
#include <vector>
#include <memory>
#include <cctype>
#include <cstring>
#include <format>

#import <objc/runtime.h>
#import <objc/message.h>

#include <libkern/OSCacheControl.h>

#include "Utilities/CGuardMemory/fishhook.h"
#include "Utilities/CGuardMemory/CGPMemory.h"

#include "Utilities/VMTHook.h"
#include "Utilities/BreakpointHook/hook.h"



ENTRY_POINT void Entry(void)
{
    // you can use this as the start point for your cheat
    // initialize globals, make threads or do whatever here
    // this function will only run once at the start of the program
    NSLog(@"Our library loaded!");
}
