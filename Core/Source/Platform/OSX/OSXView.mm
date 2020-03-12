//
// Created by Дмитрий Метелица on 2019-07-06.
//

#import "OSXView.h"
#include "Platform/Api/KeyboardInputDevice.h"
#include "Platform/Api/MouseInputDevice.h"
#import <Carbon/Carbon.h>
#import <Cocoa/Cocoa.h>

@implementation OSXView

-(instancetype)initWithWindow:(Forge::OSXWindow*)initWindow
{
    if(self = [super initWithFrame:initWindow->getWindowFrame()])
        window = initWindow;

    return self;
}

-(void)beginUpdate
{
    //updating input devices before accepting events
    //because they can be changed
    //TODO: may be its will be better to use events instead
    mouseInput = window->getInput()->getDevice<Forge::MouseInputDevice>(Forge::InputDeviceType::Mouse);
    keyboardInput = window->getInput()->getDevice<Forge::KeyboardInputDevice>(Forge::InputDeviceType::Keyborad);
}

-(void)dealloc
{
    [super dealloc];
}

-(BOOL)isOpaque
{
    return YES;
}

-(BOOL)mouseDownCanMoveWindow
{
    return YES;
}

-(BOOL)isFlipped
{
    return YES;
}

-(BOOL)acceptsFirstResponder
{
    return YES;
}

-(BOOL)acceptsFirstMouse:(__unused NSEvent*)event
{
    return YES;
}

-(BOOL)canBecomeKeyView
{
    return YES;
}

-(BOOL)wantsUpdateLayer
{
    return YES;
}

-(void)mouseDown:(NSEvent*)event
{
    if(!mouseInput)
        return;

    mouseInput->sendEvent(Forge::MouseEvent{ Forge::MouseButton::Left, Forge::KeyState::Up });
}

-(void)mouseUp:(NSEvent*)event
{
    if(!mouseInput)
        return;

    mouseInput->sendEvent(Forge::MouseEvent{ Forge::MouseButton::Left, Forge::KeyState::Up });
}

-(void)mouseMoved:(NSEvent*)event
{
    if(!mouseInput)
        return;
    //TODO: handle delta when cursor is disabled
    const NSPoint pos = [event locationInWindow];
    const NSRect contentRect = [self frame];
    // NOTE: The returned location uses base 0,1 not 0,0
    mouseInput->mousePositionChanged(Forge::Vector2(static_cast<float>(pos.x), static_cast<float>(contentRect.size.height - pos.y)));
}

-(void)mouseDragged:(NSEvent*)event
{
    [self mouseMoved:event];
}

-(void)rightMouseDown:(NSEvent*)event
{
    if(!mouseInput)
        return;

    mouseInput->sendEvent(Forge::MouseEvent{ Forge::MouseButton::Right, Forge::KeyState::Down });
}

-(void)rightMouseUp:(NSEvent*)event
{
    if(!mouseInput)
        return;

    mouseInput->sendEvent(Forge::MouseEvent{ Forge::MouseButton::Right, Forge::KeyState::Up });
}

-(void)rightMouseDragged:(NSEvent*)event
{
    [self mouseMoved:event];
}

-(void)otherMouseDown:(NSEvent*)event
{
    if(!mouseInput)
        return;

    mouseInput->sendEvent(Forge::MouseEvent{ [self getButtonById:[event buttonNumber]], Forge::KeyState::Down });
}

-(void)otherMouseUp:(NSEvent*)event
{
    if(!mouseInput)
        return;

    mouseInput->sendEvent(Forge::MouseEvent{ [self getButtonById:[event buttonNumber]], Forge::KeyState::Up });
}

-(void)otherMouseDragged:(NSEvent*)event
{
    [self mouseMoved:event];
}

-(Forge::MouseButton)getButtonById:(NSInteger)buttonNUmber
{
    switch(buttonNUmber)
    {
        case 0:
            return Forge::MouseButton::Left;
        case 1:
            return Forge::MouseButton::Right;
        case 2:
            return Forge::MouseButton::Middle;
        case 3:
            return Forge::MouseButton::XButton1;
        case 4:
            return Forge::MouseButton::XButton2;
        default:
            return Forge::MouseButton::None;
    }
}

-(void)mouseEntered:(NSEvent*)event
{
    //TODO: handle mouse entered
}

-(void)mouseExited:(NSEvent*)event
{
    //TODO: handle mouse exited
}

-(void)scrollWheel:(NSEvent*)event
{
    if(!mouseInput)
        return;
    float deltaX = static_cast<float>([event scrollingDeltaX]);
    float deltaY = static_cast<float>([event scrollingDeltaY]);

    if([event hasPreciseScrollingDeltas])
    {
        deltaX *= 0.1;
        deltaY *= 0.1;
    }

    mouseInput->wheelScrolled(Forge::Vector2(deltaX, deltaY));
}

-(void)keyDown:(NSEvent*)event
{
    if(!keyboardInput)
        return;

    keyboardInput->sendEvent(Forge::KeyboardEvent{ [self convertKey:event.keyCode], Forge::KeyState::Down });
}

-(void)keyUp:(NSEvent*)event
{
    if(!keyboardInput)
        return;

    keyboardInput->sendEvent(Forge::KeyboardEvent{ [self convertKey:event.keyCode], Forge::KeyState::Up });
}

-(Forge::KeyboardKey)convertKey:(NSInteger)key
{
    switch (key)
    {
        case kVK_UpArrow: return Forge::KeyboardKey::Up;
        case kVK_DownArrow: return Forge::KeyboardKey::Down;
        case kVK_LeftArrow: return Forge::KeyboardKey::Left;
        case kVK_RightArrow: return Forge::KeyboardKey::Right;
        case kVK_F1: return Forge::KeyboardKey::F1;
        case kVK_F2: return Forge::KeyboardKey::F2;
        case kVK_F3: return Forge::KeyboardKey::F3;
        case kVK_F4: return Forge::KeyboardKey::F4;
        case kVK_F5: return Forge::KeyboardKey::F5;
        case kVK_F6: return Forge::KeyboardKey::F6;
        case kVK_F7: return Forge::KeyboardKey::F7;
        case kVK_F8: return Forge::KeyboardKey::F8;
        case kVK_F9: return Forge::KeyboardKey::F9;
        case kVK_F10: return Forge::KeyboardKey::F10;
        case kVK_F11: return Forge::KeyboardKey::F11;
        case kVK_F12: return Forge::KeyboardKey::F12;
        case kVK_F13: return Forge::KeyboardKey::F13;
        case kVK_F14: return Forge::KeyboardKey::F14;
        case kVK_F15: return Forge::KeyboardKey::F15;
        case kVK_F16: return Forge::KeyboardKey::F16;
        case kVK_Home: return Forge::KeyboardKey::Home;
        case kVK_End: return Forge::KeyboardKey::End;
        case NSInsertFunctionKey: return Forge::KeyboardKey::Insert;
        case kVK_ForwardDelete: return Forge::KeyboardKey::Delete;
        case kVK_Help: return Forge::KeyboardKey::H;
        case NSPrintFunctionKey: return Forge::KeyboardKey::Print;
        case NSPrintScreenFunctionKey: return Forge::KeyboardKey::PrtSc;
        case NSPauseFunctionKey: return Forge::KeyboardKey::Pause;
        case NSScrollLockFunctionKey: return Forge::KeyboardKey::ScrollLock;
        case kVK_Delete: return Forge::KeyboardKey::Backspace;
        case kVK_Tab: return Forge::KeyboardKey::Tab;
        case kVK_Return: return Forge::KeyboardKey::Return;
        case kVK_Escape: return Forge::KeyboardKey::Escape;
        case kVK_Control: return Forge::KeyboardKey::LeftControl;
        case kVK_RightControl: return Forge::KeyboardKey::RightControl;
        case kVK_Command: return Forge::KeyboardKey::LeftSystem;
        case kVK_RightCommand: return Forge::KeyboardKey::RightSystem;
        case kVK_Shift: return Forge::KeyboardKey::LeftShift;
        case kVK_RightShift: return Forge::KeyboardKey::RightShift;
        case kVK_Option: return Forge::KeyboardKey::LeftAlt;
        case kVK_RightOption: return Forge::KeyboardKey::RightAlt;
        case kVK_Space: return Forge::KeyboardKey::Space;

        case kVK_ANSI_A: return Forge::KeyboardKey::A;
        case kVK_ANSI_B: return Forge::KeyboardKey::B;
        case kVK_ANSI_C: return Forge::KeyboardKey::C;
        case kVK_ANSI_D: return Forge::KeyboardKey::D;
        case kVK_ANSI_E: return Forge::KeyboardKey::E;
        case kVK_ANSI_F: return Forge::KeyboardKey::F;
        case kVK_ANSI_G: return Forge::KeyboardKey::G;
        case kVK_ANSI_H: return Forge::KeyboardKey::H;
        case kVK_ANSI_I: return Forge::KeyboardKey::I;
        case kVK_ANSI_J: return Forge::KeyboardKey::J;
        case kVK_ANSI_K: return Forge::KeyboardKey::K;
        case kVK_ANSI_L: return Forge::KeyboardKey::L;
        case kVK_ANSI_M: return Forge::KeyboardKey::M;
        case kVK_ANSI_N: return Forge::KeyboardKey::N;
        case kVK_ANSI_O: return Forge::KeyboardKey::O;
        case kVK_ANSI_P: return Forge::KeyboardKey::P;
        case kVK_ANSI_Q: return Forge::KeyboardKey::Q;
        case kVK_ANSI_R: return Forge::KeyboardKey::R;
        case kVK_ANSI_S: return Forge::KeyboardKey::S;
        case kVK_ANSI_T: return Forge::KeyboardKey::T;
        case kVK_ANSI_U: return Forge::KeyboardKey::U;
        case kVK_ANSI_V: return Forge::KeyboardKey::V;
        case kVK_ANSI_W: return Forge::KeyboardKey::W;
        case kVK_ANSI_X: return Forge::KeyboardKey::X;
        case kVK_ANSI_Y: return Forge::KeyboardKey::Y;
        case kVK_ANSI_Z: return Forge::KeyboardKey::Z;

        case kVK_ANSI_0: return Forge::KeyboardKey::Num0;
        case kVK_ANSI_1: return Forge::KeyboardKey::Num1;
        case kVK_ANSI_2: return Forge::KeyboardKey::Num2;
        case kVK_ANSI_3: return Forge::KeyboardKey::Num3;
        case kVK_ANSI_4: return Forge::KeyboardKey::Num4;
        case kVK_ANSI_5: return Forge::KeyboardKey::Num5;
        case kVK_ANSI_6: return Forge::KeyboardKey::Num6;
        case kVK_ANSI_7: return Forge::KeyboardKey::Num7;
        case kVK_ANSI_8: return Forge::KeyboardKey::Num8;
        case kVK_ANSI_9: return Forge::KeyboardKey::Num9;

        case kVK_ANSI_Comma: return Forge::KeyboardKey::Comma;
        case kVK_ANSI_Period: return Forge::KeyboardKey::Period;
        case kVK_PageUp: return Forge::KeyboardKey::PageUp;
        case kVK_PageDown: return Forge::KeyboardKey::PageDown;

        case kVK_ANSI_Keypad0: return Forge::KeyboardKey::Numpad0;
        case kVK_ANSI_Keypad1: return Forge::KeyboardKey::Numpad1;
        case kVK_ANSI_Keypad2: return Forge::KeyboardKey::Numpad2;
        case kVK_ANSI_Keypad3: return Forge::KeyboardKey::Numpad3;
        case kVK_ANSI_Keypad4: return Forge::KeyboardKey::Numpad4;
        case kVK_ANSI_Keypad5: return Forge::KeyboardKey::Numpad5;
        case kVK_ANSI_Keypad6: return Forge::KeyboardKey::Numpad6;
        case kVK_ANSI_Keypad7: return Forge::KeyboardKey::Numpad7;
        case kVK_ANSI_Keypad8: return Forge::KeyboardKey::Numpad8;
        case kVK_ANSI_Keypad9: return Forge::KeyboardKey::Numpad9;

        case kVK_ANSI_KeypadDecimal: return Forge::KeyboardKey::NumpadDecimal;
        case kVK_ANSI_KeypadMultiply: return Forge::KeyboardKey::NumpadMultiply;
        case kVK_ANSI_KeypadPlus: return Forge::KeyboardKey::NumpadPlus;
        case kVK_ANSI_KeypadClear: return Forge::KeyboardKey::NumLock;
        case kVK_ANSI_KeypadDivide: return Forge::KeyboardKey::NumpadDivide;
        case kVK_ANSI_KeypadEnter: return Forge::KeyboardKey::NumpadEnter;
        case kVK_ANSI_KeypadMinus: return Forge::KeyboardKey::NumpadMinus;

        case kVK_ANSI_Semicolon: return Forge::KeyboardKey::Semicolon;
        case kVK_ANSI_Slash: return Forge::KeyboardKey::Slash;
        case kVK_ANSI_LeftBracket: return Forge::KeyboardKey::LeftBracket;
        case kVK_ANSI_Backslash: return Forge::KeyboardKey::Backslash;
        case kVK_ANSI_RightBracket: return Forge::KeyboardKey::RightBracket;
        case 0x6E: return Forge::KeyboardKey::Menu;
        case 0x7F: return Forge::KeyboardKey::Power;

        case kVK_VolumeUp: return Forge::KeyboardKey::VolumeUp;
        case kVK_VolumeDown: return Forge::KeyboardKey::VolumeDown;
        case kVK_Mute: return Forge::KeyboardKey::VolumeMute;
        default: return Forge::KeyboardKey::None;
    }
}


-(void)resetCursorRects
{
    [super resetCursorRects];
    //TODO: process input for mac os
}


#if !defined(__MAC_10_12) || __MAC_OS_X_VERSION_MAX_ALLOWED < __MAC_10_12
enum
{
    kVK_RightCommand = 0x36
};
#endif


@end