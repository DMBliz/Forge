#include "Input.h"

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

	void Input::SetMousePositionValue(const Vector2& newPosition)
	{
		cursorPosition = newPosition;
	}

	void Input::SetScroll(const Vector2& scroll)
	{
		wheelDelta = scroll;
	}

	void Input::SetCharacterPressed(uint character)
	{
		onCharacterPressed(character);
	}

	Input::Input()
	{
		for(int i = 0; i < static_cast<int>(MouseButton::ButtonCount); i++)
		{
			mouseButtons[i] = InputState::None;
			prevMouseButtons[i] = InputState::None;
		}

		for (int i = 0; i < static_cast<int>(KeyboardKey::KeyCount); i++)
		{
			keyboardKeys[i] = InputState::None;
			prevKeyboardKeys[i] = InputState::None;
		}
	}

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

	const Vector2& Input::GetCursorPosition()
	{
		return cursorPosition;
	}

	const Vector2& Input::GetCursorDelta()
	{
		return deltaCursorPosition;
	}

	const Vector2& Input::GetMouseWheelDelta()
	{
		return wheelDelta;
	}

	void Input::Update()
	{
		uint keyCount = static_cast<uint>(KeyboardKey::KeyCount);
		for (int i = 0; i < keyCount; ++i)
		{
			if ((prevKeyboardKeys[i] == InputState::Down && keyboardKeys[i] == InputState::Down) || (prevKeyboardKeys[i] == InputState::Hold && keyboardKeys[i] == InputState::Hold) || (prevKeyboardKeys[i] == InputState::Hold && keyboardKeys[i] == InputState::Down))
				keyboardKeys[i] = InputState::Hold;

			if (prevKeyboardKeys[i] == InputState::Up)
				keyboardKeys[i] = InputState::None;

			if (keyboardKeys[i] != prevKeyboardKeys[i])
			{
				onKeyStateChanged(static_cast<KeyboardKey>(i), keyboardKeys[i]);
			}

			prevKeyboardKeys[i] = keyboardKeys[i];
		}

		uint buttonCount = static_cast<uint>(MouseButton::ButtonCount);

		for (int i = 0; i < buttonCount; ++i)
		{
			if ((prevMouseButtons[i] == InputState::Down && mouseButtons[i] == InputState::Down) || (prevMouseButtons[i] == InputState::Hold && mouseButtons[i] == InputState::Hold) || (prevMouseButtons[i] == InputState::Hold && mouseButtons[i] == InputState::Down))
				mouseButtons[i] = InputState::Hold;

			if (prevMouseButtons[i] == InputState::Up)
				mouseButtons[i] = InputState::None;

			if (mouseButtons[i] != prevMouseButtons[i])
			{
				onMouseButtonStateChanged(static_cast<MouseButton>(i), mouseButtons[i]);
			}

			prevMouseButtons[i] = mouseButtons[i];
		}

		if (prevCursorPosition != cursorPosition)
			onCursorMove(cursorPosition);

		deltaCursorPosition = cursorPosition - prevCursorPosition;
		prevCursorPosition = cursorPosition;

		if (prevWheelDelta != wheelDelta)
			onMouseWheelScroll(wheelDelta);
		else if (prevWheelDelta == wheelDelta)
			wheelDelta = Vector2::Zero;

		prevWheelDelta = wheelDelta;
	}

	void Input::SetMousePosition(const Vector2& newPosition)
	{
        cursorPosition = newPosition;
	}
}
