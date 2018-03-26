#pragma once
#include "imgui/ImGui.h"
#include "Math/Vector2i.h"
#include "Core/Engine.h"
#include "GUIScene.h"
#include "GUIProperties.h"
#include "GUIHierarchy.h"
#include "GUIResources.h"

namespace ForgeEditor
{
	bool showScene = false;
	bool showProperties = false;
	bool showEntitys = false;
	bool showResources = false;

	//bool settings = true;

	inline void Update()
	{
		ImGui::Begin("Settings");

		ImGui::Checkbox("Scene", &showScene);
		ImGui::Checkbox("Properties", &showProperties);
		ImGui::Checkbox("Hierarchy", &showEntitys);
		ImGui::Checkbox("Resources", &showResources);

		ImGui::End();

		if(showScene)
		{
			DrawScene(showScene);
            
		}
		
		if(showEntitys)
		{
			DrawHierarchy(showEntitys, Forge::engine->GetScene());
		}

		if(showResources)
		{
			DrawResources(showResources);
		}

		if(showProperties)
		{
			DrawProperties(showProperties, selectedEntity);
		}
	}
}
