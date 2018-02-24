#pragma once
#include "Math/Vector2i.h"
#include "Containers/String.h"
#include <mutex>
#include "Defines.h"
#include "EventSystem/Event.h"
#include "Graphics/Context.h"
#include "Math/Vector2.h"

namespace Forge
{
	class Window
	{
		friend class Input;
	public:

		Event<void(const Vector2i&)> onSizeChanged;

	protected:
		Vector2i windowSize;
		Vector2i windowResolution;
		Vector2i framebufferSize;

		float contentScale = 1.0f;
		bool resizable = false;
		bool fullScreen = false;
		bool exclusiveFullScreen = false;
		bool highDPI = true;
		String windowTitle;
		Context* context;

		bool hasFocus = true;

		virtual void SetCursorPosition(const Vector2i& newPos) = 0;

	public:

		static Window* GetInstance();

		virtual void Create(const Vector2i& size, const String& title, bool Resizable, bool FullScreen, bool ExclusiveFullScreen, bool HighDPI, bool depth) = 0;
		virtual void CreateContext() = 0;
		virtual void Close() {}

		const Vector2i& GetSize() const { return windowSize; }
		virtual void SetSize(const Vector2i& newSize) { windowSize = newSize; }

		const Vector2i& GetResolution() const { return windowResolution; }
		float GetContentScale() const { return contentScale; }

		virtual void SetFullScreen(bool value) { fullScreen = value; }
		bool IsFullScreen() const { return fullScreen; }

		bool IsFocused() const { return hasFocus; }

		bool IsExclusiveFullScreen() const { return exclusiveFullScreen; }

		const String& GetTitle() const { return windowTitle; }
		virtual void SetTitle(const String& newTitle) { windowTitle = newTitle; }

		virtual void PlatformUpdate() = 0;

		virtual void SetClipboard(const String& data) = 0;
		virtual const String& GetClipboard() = 0;

		const Vector2i& GetFrameBufferSize() { return framebufferSize; }
	};
}
