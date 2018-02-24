#pragma once
#include "imgui/ImGui.h"
#include "Math/Vector2i.h"
#include "Core/Engine.h"
#include "GUICamera.h"

namespace ForgeEditor
{
	ImVec2 windowSize;

	inline void DrawScene(bool& drawScene)
	{
		Forge::Texture2D* tex = Forge::engine->GetRenderer()->GetScreenTexture();
		ImGui::Begin("Scene", &drawScene);
		if (ImGui::GetWindowHeight() != windowSize.x || ImGui::GetWindowWidth() != windowSize.y)
		{
			windowSize = ImGui::GetWindowSize();
			Forge::engine->GetRenderer()->SetSize(Forge::Vector2i(windowSize.x, (windowSize.y - 35) <= 0 ? 1 : windowSize.y - 35));
			if(ImGui::IsWindowFocused())
			{
				UpdateCamera();
				Forge::engine->GetRenderer()->SetViewMatrix(GetViewMatrix());
			}
		}
		ImGui::Image(reinterpret_cast<void*>(tex->GetID()), ImVec2(tex->GetSize().x, tex->GetSize().y));
		ImGui::End();
	}
}
