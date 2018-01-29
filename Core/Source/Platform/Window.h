#pragma once
#include "Math/Vector2i.h"
#include "Containers/String.h"
#include <mutex>
#include "Defines.h"

namespace Forge
{
	class Window
	{
	public:

		struct Listener
		{
		public:
			virtual ~Listener() = 0;
			virtual void onSizeChange(const Vector2i& newSize) = 0;
			virtual void onResolutionChange(const Vector2i& newResolution) = 0;
			virtual void onFullscreenChange(bool newFullscreen) = 0;
			virtual void onScreenChange(uint32_t newDisplayId) = 0;
			virtual void onClose() = 0;
		};

	protected:
		Vector2i windowSize;
		Vector2i windowResolution;
		float contentScale = 1.0f;
		bool resizable = false;
		bool fullScreen = false;
		bool exclusiveFullScreen = false;
		bool highDPI = true;


		std::mutex listenerMutex;
		Listener* listener = nullptr;
		String windowTitle;
	public:

		static Window* GetInstance();

		virtual void Create(const Vector2i& size, const String& title, bool Resizable, bool FullScreen, bool ExclusiveFullScreen, bool HighDPI, bool depth) = 0;
		virtual void Close() {}

		const Vector2i& GetSize() const { return windowSize; }
		virtual void SetSize(const Vector2i& newSize) { windowSize = newSize; }

		const Vector2i& GetResolution() const { return windowResolution; }
		float GetContentScale() const { return contentScale; }

		virtual void SetFullScreen(bool value) { fullScreen = value; }
		bool IsFullScreen() const { return fullScreen; }

		bool IsExclusiveFullScreen() const { return exclusiveFullScreen; }

		const String& GetTitle() const { return windowTitle; }
		virtual void SetTitle(const String& newTitle) { windowTitle = newTitle; }

		void SetListener(Listener* newListener) { std::unique_lock<std::mutex> lock(listenerMutex);  listener = newListener; }
	};
}
