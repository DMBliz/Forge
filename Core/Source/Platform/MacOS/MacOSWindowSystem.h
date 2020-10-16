//
// Created by Dmitry Metelitsa on 10/17/20.
//

#pragma once

#include "Platform/Api/WindowSystem.h"

#if defined(__OBJC__)
@class NSAutoreleasePool;
@class NSApplication;

typedef NSApplication* NSApplicationPtr;
typedef NSAutoreleasePool* NSAutoreleasePoolPtr;
#else
#include <objc/NSObjCRuntime.h>
typedef id NSApplicationPtr;
typedef id NSAutoreleasePoolPtr;
#endif

namespace Forge
{
    class MacOSWindowSystem : public WindowSystem
    {

    };
}