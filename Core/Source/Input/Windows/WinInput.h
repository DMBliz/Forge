#pragma once
#include "Input/Input.h"
#include <windows.h>

namespace Forge
{

	class WinInput : public Input
	{
	public:
		WinInput();
		~WinInput();

		void SetKeyStateNative(UINT key, InputState state);
		void SetKeyUpNative(UINT key);
		void SetKeyDownNative(UINT key);

		void SetButtonStateNative(UINT key, InputState state);
		void SetButtonUpNative(MouseButton key);
		void SetButtonDownNative(MouseButton key);

		void SetMousePosition(const Vector2& newPosition) override;
	};

}
