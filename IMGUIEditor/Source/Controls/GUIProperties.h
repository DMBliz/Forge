#pragma once
#include <vector>
#include "Scene/Component.h"
#include "Core/Engine.h"
#include "Scene/TransformComponent.h"
#include "Scene/SpriteRenderer.h"
#include "imgui/imgui.h"
#include "GUIResources.h"

namespace ForgeEditor
{
	std::vector<Forge::String> componentNames = { "Transform", "Sprite" };

	inline void DrawComponent(Forge::Component* component)
	{
		
	}

	inline void DrawComponent(Forge::TransformComponent* component)
	{

		Forge::Vector3 pos = component->Position();
		Forge::Vector3 rot = component->Rotation().EulerAngles();
		Forge::Vector3 sc = component->Scale();

		ImGui::DragFloat3("Position", &pos.x);
		ImGui::DragFloat3("Rotation", &rot.x);
		ImGui::DragFloat3("Scale", &sc.x);

		Forge::Vector3 rt = component->Rotation().EulerAngles();
		if(pos != component->Position())
		{
			component->Position(pos);
		}
		if(rot != rt)
		{
			component->Rotation(Forge::Quaternion::FromEuler(rot));
		}
		if(sc != component->Scale())
		{
			component->Scale(sc);
		}
	}

	inline void DrawComponent(Forge::SpriteRenderer* component)
	{
		Forge::String butName;
		Forge::Texture2D* tx = component->GetTexture();
		if(tx != nullptr)
		{
			if(tx->GetResourceName() != Forge::String::Empty)
			{
				butName = tx->GetResourceName();
			}else
			{
				butName = "NotSet";
			}
		}else
		{
			butName = "NotSet";
		}
		//TODO: this and add here shader
		ImGui::Text("Texture");
		ImGui::SameLine();
		if(ImGui::Button(butName.CString()))
		{
			ImGui::OpenPopup("Texture");
		}
		Forge::String selectedRes = Forge::String::Empty;
		if (ImGui::BeginPopup("Texture"))
		{
			for(const Forge::String& resourceName : ress)
			{
				if(resourceName.Contains(".png") || resourceName.Contains(".jpg"))
				{
					if(ImGui::Button(resourceName.CString()))
					{
						selectedRes = resourceName;
						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndPopup();
		}

		if(selectedRes != Forge::String::Empty)
		{
			component->SetTexture(Forge::engine->GetResources()->LoadNowResource<Forge::Texture2D>(selectedRes));
		}
		
	}

	inline void Resolve(Forge::Component* component)
	{
		if(typeid(*component) == typeid(Forge::TransformComponent))
		{
			if (ImGui::CollapsingHeader("Transform Component"))
			{
				Forge::TransformComponent* rend = static_cast<Forge::TransformComponent*>(component);
				DrawComponent(rend);
			}
		}

		if (typeid(*component) == typeid(Forge::SpriteRenderer))
		{
			if (ImGui::CollapsingHeader("Sprite Renderer"))
			{
				Forge::SpriteRenderer* rend = static_cast<Forge::SpriteRenderer*>(component);
				DrawComponent(rend);
			}
		}
	}

	inline void DrawProperties(bool& draw, Forge::Entity* entity)
	{
		ImGui::Begin("Properties", &draw);
		if (entity != nullptr)
		{
			std::vector<Forge::Component*> components = entity->GetAllComponents();
			for (Forge::Component* component : components)
			{
				Resolve(component);
				
			}
			if(ImGui::Button("Add Component",ImVec2(ImGui::GetWindowWidth(), 20)))
			{
				ImGui::OpenPopup("component");
			}

			if(ImGui::BeginPopup("component"))
			{
				for(const Forge::String& componentName : componentNames)
				{
					if(ImGui::Button(componentName.CString()))
					{
						if(componentName == "Transform")
						{
							entity->AddComponent<Forge::TransformComponent>();
						}
						if(componentName == "Sprite")
						{
							entity->AddComponent<Forge::SpriteRenderer>();
						}
						ImGui::CloseCurrentPopup();
					}
				}
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}
