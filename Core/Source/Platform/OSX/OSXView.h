//
// Created by Дмитрий Метелица on 2019-07-06.
//

#pragma once

#import <Platform/Api/MouseInputDevice.h>
#import <Platform/Api/KeyboardInputDevice.h>
#import "AppKit/AppKit.h"
#import "OSXWindow.h"

@interface OSXView: NSView
{
    Forge::Window* window;
    Forge::MouseInputDevice* mouseInput;
    Forge::KeyboardInputDevice* keyboardInput;
}

-(instancetype)initWithWindow:(Forge::OSXWindow*)initWindow;
-(void)beginUpdate;

@end


