#include "Input.h"
#include "Windows/WinInput.h"
#include "Defines.h"

namespace Forge
{
	void Input::SetKeyState(KeyboardKey key, InputState state)
	{
		keyboardKeys[static_cast<uint>(key)] = state;
	}

	void Input::SetButtonState(MouseButton button, InputState state)
	{
		mouseButtons[static_cast<uint>(button)] = state;
	}

	void Input::SetMousePosition(const Vector2& newPosition)
	{
		cursorPosition = newPosition;
	}

	Input::Input()
	{}

	Input::~Input()
	{}

	bool Input::KeyHold(KeyboardKey key)
	{
		return keyboardKeys[static_cast<uint>(key)] == InputState::Hold;
	}

	bool Input::KeyDown(KeyboardKey key)
	{
		return keyboardKeys[static_cast<uint>(key)] == InputState::Down;
	}

	bool Input::KeyRelease(KeyboardKey key)
	{
		return keyboardKeys[static_cast<uint>(key)] == InputState::Up;
	}

	bool Input::MouseButtonHold(MouseButton button)
	{
		return mouseButtons[static_cast<uint>(button)] == InputState::Hold;
	}

	bool Input::MouseButtonDown(MouseButton button)
	{
		return mouseButtons[static_cast<uint>(button)] == InputState::Down;
	}

	bool Input::MouseButtonRelease(MouseButton button)
	{
		return mouseButtons[static_cast<uint>(button)] == InputState::Up;
	}

	InputState Input::GetKeyState(KeyboardKey key)
	{
		return keyboardKeys[static_cast<uint>(key)];
	}

	InputState Input::GetMouseButtonState(MouseButton button)
	{
		return mouseButtons[static_cast<uint>(button)];
	}

	void Input::Update()
	{
		uint keyCount = static_cast<uint>(KeyboardKey::KeyCount);

		for (int i = 0; i < keyCount; ++i)
		{
			if (prevKeyboardKeys[i] == InputState::Down && keyboardKeys[i] == InputState::Down || prevKeyboardKeys[i] == InputState::Hold && keyboardKeys[i] == InputState::Hold || prevKeyboardKeys[i] == InputState::Hold && keyboardKeys[i] == InputState::Down)
				keyboardKeys[i] = InputState::Hold;

			if (prevKeyboardKeys[i] == InputState::Up)
				keyboardKeys[i] = InputState::None;

			if (keyboardKeys[i] == InputState::Down)
			{
				LOG(String(i) + " Is Down");
			}

			if (keyboardKeys[i] == InputState::Up)
			{

				LOG(String(i) + " Is Up");
			}

			if (keyboardKeys[i] == InputState::Hold)
			{

				LOG(String(i) + " Is hold");
			}
			prevKeyboardKeys[i] = keyboardKeys[i];
		}
	}

	Input* Input::Create()
	{
#if defined(WIN32)
		return new WinInput();
#elif defined(MACOS)
#elif defined(ANDROID)
#elif defined(IOS)
#endif
	}
}
