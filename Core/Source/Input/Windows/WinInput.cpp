#include "WinInput.h"
#include <map>
#include "Core/Engine.h"
#include "Platform/Windows/WindowWin32.h"

namespace Forge
{
	static const std::map<UINT, KeyboardKey> keyMap = {
		{ 'A',			 KeyboardKey::A },
		{ 'B',			 KeyboardKey::B },
		{ 'C',			 KeyboardKey::C },
		{ 'D',			 KeyboardKey::D },
		{ 'E',			 KeyboardKey::E },
		{ 'F',			 KeyboardKey::F },
		{ 'G',			 KeyboardKey::G },
		{ 'H',			 KeyboardKey::H },
		{ 'I',			 KeyboardKey::I },
		{ 'J',			 KeyboardKey::J },
		{ 'K',			 KeyboardKey::K },
		{ 'L',			 KeyboardKey::L },
		{ 'M',			 KeyboardKey::M },
		{ 'N',			 KeyboardKey::N },
		{ 'O',			 KeyboardKey::O },
		{ 'P',			 KeyboardKey::P },
		{ 'Q',			 KeyboardKey::Q },
		{ 'R',			 KeyboardKey::R },
		{ 'S',			 KeyboardKey::S },
		{ 'T',			 KeyboardKey::T },
		{ 'U',			 KeyboardKey::U },
		{ 'V',			 KeyboardKey::V },
		{ 'W',			 KeyboardKey::W },
		{ 'X',			 KeyboardKey::X },
		{ 'Y',			 KeyboardKey::Y },
		{ 'Z',			 KeyboardKey::Z },
		{ '0',			 KeyboardKey::Num0 },
		{ '1',			 KeyboardKey::Num1 },
		{ '2',			 KeyboardKey::Num2 },
		{ '3',			 KeyboardKey::Num3 },
		{ '4',			 KeyboardKey::Num4 },
		{ '5',			 KeyboardKey::Num5 },
		{ '6',			 KeyboardKey::Num6 },
		{ '7',			 KeyboardKey::Num7 },
		{ '8',			 KeyboardKey::Num8 },
		{ '9',			 KeyboardKey::Num9 },
		{ VK_ESCAPE,	 KeyboardKey::Escape },
		{ VK_LCONTROL,	 KeyboardKey::LControl },
		{ VK_LSHIFT,	 KeyboardKey::LShift },
		{ VK_LMENU,		 KeyboardKey::LAlt },
		{ VK_LWIN,		 KeyboardKey::LSystem },
		{ VK_RCONTROL,	 KeyboardKey::RControl },
		{ VK_RSHIFT,	 KeyboardKey::RShift },
		{ VK_RMENU,		 KeyboardKey::RAlt },
		{ VK_RWIN,		 KeyboardKey::RSystem },
		{ VK_APPS,		 KeyboardKey::Menu },
		{ VK_OEM_4,		 KeyboardKey::LBracket },
		{ VK_OEM_6,		 KeyboardKey::RBracket },
		{ VK_OEM_1,		 KeyboardKey::SemiColon },
		{ VK_OEM_COMMA,	 KeyboardKey::Comma },
		{ VK_OEM_PERIOD, KeyboardKey::Period },
		{ VK_OEM_7,		 KeyboardKey::Quote },
		{ VK_OEM_2,		 KeyboardKey::Slash },
		{ VK_OEM_5,		 KeyboardKey::BackSlash},
		{ VK_OEM_3,		 KeyboardKey::Tilde },
		{ VK_OEM_PLUS,	 KeyboardKey::Equal },
		{ VK_OEM_MINUS,	 KeyboardKey::Dash },
		{ VK_SPACE,		 KeyboardKey::Space },
		{ VK_RETURN,	 KeyboardKey::Return },
		{ VK_BACK,		 KeyboardKey::BackSpace },
		{ VK_TAB,		 KeyboardKey::Tab },
		{ VK_PRIOR,		 KeyboardKey::PageUp },
		{ VK_NEXT,		 KeyboardKey::PageDown },
		{ VK_END,		 KeyboardKey::End },
		{ VK_HOME,		 KeyboardKey::Home },
		{ VK_INSERT,	 KeyboardKey::Insert },
		{ VK_DELETE,	 KeyboardKey::Delete },
		{ VK_ADD,		 KeyboardKey::Add },
		{ VK_SUBTRACT,	 KeyboardKey::Subtract },
		{ VK_MULTIPLY,	 KeyboardKey::Multiply },
		{ VK_DIVIDE,	 KeyboardKey::Divide },
		{ VK_LEFT,		 KeyboardKey::Left },
		{ VK_RIGHT,		 KeyboardKey::Right },
		{ VK_UP,		 KeyboardKey::Up },
		{ VK_DOWN,		 KeyboardKey::Down },
		{ VK_NUMPAD0,	 KeyboardKey::Numpad0 },
		{ VK_NUMPAD1,	 KeyboardKey::Numpad1 },
		{ VK_NUMPAD2,	 KeyboardKey::Numpad2 },
		{ VK_NUMPAD3,	 KeyboardKey::Numpad3 },
		{ VK_NUMPAD4,	 KeyboardKey::Numpad4 },
		{ VK_NUMPAD5,	 KeyboardKey::Numpad5 },
		{ VK_NUMPAD6,	 KeyboardKey::Numpad6 },
		{ VK_NUMPAD7,	 KeyboardKey::Numpad7 },
		{ VK_NUMPAD8,	 KeyboardKey::Numpad8 },
		{ VK_NUMPAD9,	 KeyboardKey::Numpad9 },
		{ VK_F1,		 KeyboardKey::F1 },
		{ VK_F2,		 KeyboardKey::F2 },
		{ VK_F3,		 KeyboardKey::F3 },
		{ VK_F4,		 KeyboardKey::F4 },
		{ VK_F5,		 KeyboardKey::F5 },
		{ VK_F6,		 KeyboardKey::F6 },
		{ VK_F7,		 KeyboardKey::F7 },
		{ VK_F8,		 KeyboardKey::F8 },
		{ VK_F9,		 KeyboardKey::F9 },
		{ VK_F10,		 KeyboardKey::F10 },
		{ VK_F11,		 KeyboardKey::F11 },
		{ VK_F12,		 KeyboardKey::F12 },
		{ VK_F13,		 KeyboardKey::F13 },
		{ VK_F14,		 KeyboardKey::F14 },
		{ VK_F15,		 KeyboardKey::F15 },
		{ VK_F16,		 KeyboardKey::F16 },
		{ VK_PAUSE,		 KeyboardKey::Pause },
		{ VK_CAPITAL,	 KeyboardKey::CapsLock },
		{ VK_SNAPSHOT,	 KeyboardKey::PrtSc}
	};

	WinInput::WinInput()
	{}


	WinInput::~WinInput()
	{}

	void WinInput::SetKeyStateNative(UINT key, InputState state)
	{
		KeyboardKey keyboardKey = KeyboardKey::None;
		auto i = keyMap.find(key);
		if(i != keyMap.end())
		{
			keyboardKey = i->second;
			SetKeyState(keyboardKey, state);
		}
	}

	void WinInput::SetKeyUpNative(UINT key)
	{
		KeyboardKey keyboardKey = KeyboardKey::None;
		auto i = keyMap.find(key);
		if (i != keyMap.end())
		{
			keyboardKey = i->second;
			SetKeyState(keyboardKey, InputState::Up);
		}
	}

	void WinInput::SetKeyDownNative(UINT key)
	{
		KeyboardKey keyboardKey = KeyboardKey::None;
		auto i = keyMap.find(key);
		if (i != keyMap.end())
		{
			keyboardKey = i->second;
			SetKeyState(keyboardKey, InputState::Down);
		}
	}

	void WinInput::SetScrollNative(const Vector2& scroll)
	{
		SetScroll(scroll);
	}

	void WinInput::SetButtonStateNative(UINT key, InputState state)
	{
		switch(key)
		{
			case VK_LBUTTON: SetButtonState(MouseButton::Left, state); break;
			case VK_RBUTTON: SetButtonState(MouseButton::Right, state); break;
			case VK_MBUTTON: SetButtonState(MouseButton::Middle, state); break;
			case VK_XBUTTON1: SetButtonState(MouseButton::XButton1, state); break;
			case VK_XBUTTON2: SetButtonState(MouseButton::XButton2, state); break;
		}
	}

	void WinInput::SetButtonUpNative(MouseButton key)
	{
		SetButtonState(key, InputState::Up);
	}

	void WinInput::SetButtonDownNative(MouseButton key)
	{
		SetButtonState(key, InputState::Down);
	}

	void WinInput::SetMousePosition(const Vector2& newPosition)
	{
		static_cast<WindowWin32*>(engine->GetWindow())->SetCursorPosition(Vector2i(static_cast<int>(newPosition.x), static_cast<int>(newPosition.y)));
	}

	void WinInput::SetMousePositionValue(const Vector2& newPosition)
	{
		Input::SetMousePositionValue(newPosition);
	}

	void WinInput::SetCharacterPressed(uint character)
	{
		Input::SetCharacterPressed(character);
	}
}
