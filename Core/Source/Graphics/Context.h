#pragma once

#include "Math/Color.h"
#include "Math/Vector2i.h"


namespace Forge
{
	class Window;

	class Context
	{
	protected:
		Color clearColor;
		float clearDepth = 1.0f;

		bool clearColorBuffer = true;
		bool clearDepthBuffer = false;

		Vector2i size;

		unsigned int sampleCount = 1;
		bool depth = false;
		bool debugRenderer = false;
	public:
		Context();

		virtual void Init(const Window& win, unsigned int sampleCount, bool depth, bool debugRenderer);

		virtual void Draw() = 0;
		virtual void swapBuffers() = 0;

		virtual void SetSize(const Vector2i& newSize) { size = newSize; }
		const Vector2i& GetSize() { return size; }

		virtual void SetClearColorBuffer(bool value) { clearColorBuffer = value; }
		bool GetClearColorBuffer() { return clearColorBuffer; }

		virtual void SetClearDepthBuffer(bool value) { clearDepthBuffer = value; }
		bool GetClearDepthBuffer() { return clearDepthBuffer; }

		virtual void SetClearColor(const Color& color) { clearColor = color; }
		const Color& GetClearColor() { return clearColor; }

		virtual void SetClearDepth(float depth) { clearDepth = depth; }
		float GetClearDepth() { return clearDepth; }

	};

}
