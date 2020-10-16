//
// Created by Dmitry Metelitsa on 2019-07-06.
//

#pragma once

#import <Platform/Api/MouseInputDevice.h>
#import <Platform/Api/KeyboardInputDevice.h>
#import "AppKit/AppKit.h"
#import "MacOSWindow.h"

@interface MacOSView: NSView
{
    Forge::Window* window;
    Forge::MouseInputDevice* mouseInput;
    Forge::KeyboardInputDevice* keyboardInput;
}

-(instancetype)initWithWindow:(Forge::MacOSWindow*)initWindow;
-(void)beginUpdate;

@end


