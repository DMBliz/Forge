//
// Created by Dmitry Metelitsa on 2/25/20.
//

#pragma once

#include "Math/Vector2.h"
#include "InputDevice.h"
#include "Types.h"

namespace Forge
{
    enum class KeyboardKey
    {
        None = -1,          ///< Unhandled key
        A = 0,              ///< The A key
        B,                  ///< The B key
        C,                  ///< The C key
        D,                  ///< The D key
        E,                  ///< The E key
        F,                  ///< The F key
        G,                  ///< The G key
        H,                  ///< The H key
        I,                  ///< The I key
        J,                  ///< The J key
        K,                  ///< The K key
        L,                  ///< The L key
        M,                  ///< The M key
        N,                  ///< The N key
        O,                  ///< The O key
        P,                  ///< The P key
        Q,                  ///< The Q key
        R,                  ///< The R key
        S,                  ///< The S key
        T,                  ///< The T key
        U,                  ///< The U key
        V,                  ///< The V key
        W,                  ///< The W key
        X,                  ///< The X key
        Y,                  ///< The Y key
        Z,                  ///< The Z key
        Num0,               ///< The 0 key
        Num1,               ///< The 1 key
        Num2,               ///< The 2 key
        Num3,               ///< The 3 key
        Num4,               ///< The 4 key
        Num5,               ///< The 5 key
        Num6,               ///< The 6 key
        Num7,               ///< The 7 key
        Num8,               ///< The 8 key
        Num9,               ///< The 9 key

        Escape,             ///< The Escape key
        LeftControl,        ///< The left Control key
        LeftShift,          ///< The left Shift key
        LeftAlt,            ///< The left Alt key
        LeftSystem,         ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RightControl,       ///< The right Control key
        RightShift,         ///< The right Shift key
        RightAlt,           ///< The right Alt key
        RightSystem,        ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu,               ///< The Menu key

        LeftBracket,        ///< The [ key
        RightBracket,       ///< The ] key
        Semicolon,          ///< The ; key
        Comma,              ///< The , key
        Period,             ///< The . key
        Quote,              ///< The ' key
        Slash,              ///< The / key
        Backslash,          ///< The \ key
        Tilde,              ///< The ~ key
        Equal,              ///< The = key
        Dash,               ///< The - key

        Space,              ///< The Space key
        Return,             ///< The Return key
        Backspace,          ///< The Backspace key
        Tab,                ///< The Tabulation key

        PageUp,             ///< The Page up key
        PageDown,           ///< The Page down key
        End,                ///< The End key
        Home,               ///< The Home key
        Insert,             ///< The Insert key
        Delete,             ///< The Delete key

        Plus,               ///< The + key
        Minus,              ///< The - key
        Multiply,           ///< The * key
        Divide,             ///< The / key

        Left,               ///< Left arrow
        Right,              ///< Right arrow
        Up,                 ///< Up arrow
        Down,               ///< Down arrow

        Numpad0,            ///< The numpad 0 key
        Numpad1,            ///< The numpad 1 key
        Numpad2,            ///< The numpad 2 key
        Numpad3,            ///< The numpad 3 key
        Numpad4,            ///< The numpad 4 key
        Numpad5,            ///< The numpad 5 key
        Numpad6,            ///< The numpad 6 key
        Numpad7,            ///< The numpad 7 key
        Numpad8,            ///< The numpad 8 key
        Numpad9,            ///< The numpad 9 key
        NumpadPlus,         ///< The + key on Numpad
        NumpadMinus,        ///< The - key on Numpad
        NumpadMultiply,     ///< The * key on Numpad
        NumpadDivide,       ///< The / key on Numpad
        NumpadEnter,        ///< The Enter key on Numpad
        NumpadDecimal,      ///< The decimal key on Numpad

        F1,                 ///< The F1 key
        F2,                 ///< The F2 key
        F3,                 ///< The F3 key
        F4,                 ///< The F4 key
        F5,                 ///< The F5 key
        F6,                 ///< The F6 key
        F7,                 ///< The F7 key
        F8,                 ///< The F8 key
        F9,                 ///< The F9 key
        F10,                ///< The F10 key
        F11,                ///< The F11 key
        F12,                ///< The F12 key
        F13,                ///< The F13 key
        F14,                ///< The F14 key
        F15,                ///< The F15 key
        F16,                ///< The F16 key

        VolumeUp,           ///< The Volume up key
        VolumeDown,         ///< The Volume down key
        VolumeMute,         ///< The mute Volume key

        Pause,              ///< The Pause key

        CapsLock,	        ///< The Caps Lock key
        NumLock,	        ///< The Numpad Lock key
        ScrollLock,	        ///< The Scroll Lock key

        PrtSc,		        ///< The Print Screen key

        Print,              ///< The Print key

        Power,              //< The power key

        KeyCount            ///< Keep last -- the total number of keyboard keys
    };

    struct KeyboardEvent
    {
        KeyboardKey key;
        KeyState state;
    };

    class KeyboardInputDevice : public InputDevice
    {
    private:
        KeyState keyboardKeys[static_cast<uint>(KeyboardKey::KeyCount)];
        KeyState prevKeyboardKeys[static_cast<uint>(KeyboardKey::KeyCount)];
    public:
        void update() override;

        void sendEvent(const KeyboardEvent& event);

        KeyState getKeyState(KeyboardKey key) const;

        InputDeviceType getType() override;
    };
}