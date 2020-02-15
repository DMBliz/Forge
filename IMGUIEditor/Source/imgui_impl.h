#pragma once
#include "imgui/imgui.h"
#include "Platform/Api/Window.h"


namespace Forge {
	class Vector2;
	enum class MouseButton;
	enum class KeyboardKey;
	enum class InputState : unsigned char;
}

IMGUI_API bool        ImGui_Init(Forge::Window* window, bool install_callbacks);
IMGUI_API void        ImGui_Shutdown();
IMGUI_API void        ImGui_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
IMGUI_API void        ImGui_MouseButtonCallback(Forge::MouseButton button, Forge::InputState state);
IMGUI_API void        ImGui_ScrollCallback(const Forge::Vector2& scroll);
IMGUI_API void        ImGui_KeyCallback(Forge::KeyboardKey key, Forge::InputState state);
IMGUI_API void        ImGui_CharCallback(unsigned int c);
