#pragma once
#include <vector>
#include "Scene/Component.h"
#include "Core/Engine.h"
#include "Scene/TransformComponent.h"
#include "Scene/SpriteRenderer.h"
#include "imgui/imgui.h"
#include "GUIResources.h"
#include "Scene/ModelRenderer.h"
#include "Scene/PointLightComponent.h"
#include "Scene/SpotLightComponent.h"
#include "Scene/DirectionalLightComponent.h"

namespace ForgeEditor
{
	inline void DrawComponent(Forge::ModelRenderer* component)
	{
		Forge::String butName;
		Forge::Model* mdl = component->GetModel();
		if (mdl != nullptr)
		{
			if (mdl->GetResourceName() != Forge::String::Empty)
			{
				butName = mdl->GetResourceName();
			}
			else
			{
				butName = "NotSet";
			}
		}
		else
		{
			butName = "NotSet";
		}
		ImGui::Text("Model");
		ImGui::SameLine();
		if (ImGui::Button(butName.CString()))
		{
			ImGui::OpenPopup("Model");
		}
		Forge::String selectedRes = Forge::String::Empty;
		if (ImGui::BeginPopup("Model"))
		{
			for (const Forge::String& resourceName : ress)
			{
				if (resourceName.Contains(".obj") || resourceName.Contains(".fbx") || resourceName.Contains(".blend"))
				{
					if (ImGui::Button(resourceName.CString()))
					{
						selectedRes = resourceName;
						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndPopup();
		}

		if (selectedRes != Forge::String::Empty)
		{
			component->SetModel(Forge::engine->GetResources()->LoadNowResource<Forge::Model>(selectedRes));
		}
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

    inline void DrawComponent(Forge::PointLightComponent* component)
    {
        Forge::PointLight* light = component->GetLight();
        Forge::Vector4 color = light->GetColor().GetNormalizedVector();
        

        float colorf[4] = { color.x, color.y, color.z, color.w };
        float linear = light->Linear();
        float quadratic = light->Quadratic();

        ImGui::ColorEdit4("Light color", colorf);
        ImGui::DragFloat("Linear", &linear);
        ImGui::DragFloat("Quadratic", &quadratic);

        if (color.x != colorf[0] || color.y != colorf[1] || color.z != colorf[2] || color.w != colorf[3])
        {
            light->SetColor(Forge::Color(colorf[0], colorf[1], colorf[2], colorf[3]));
        }

        if (linear != light->Linear())
        {
            light->Linear(linear);
        }

        if (quadratic != light->Quadratic())
        {
            light->Quadratic(quadratic);
        }
    }

    inline void DrawComponent(Forge::SpotLightComponent* component)
    {
        Forge::SpotLight* light = component->GetLight();
        Forge::Vector4 color = light->GetColor().GetNormalizedVector();


        float colorf[4] = { color.x, color.y, color.z, color.w };
        float cutOff = light->CutOff();
        float outerCutOff = light->OuterCutOff();
        float linear = light->Linear();
        float quadratic = light->Quadratic();

        ImGui::ColorEdit4("Light color", colorf);
        ImGui::DragFloat("Linear", &linear);
        ImGui::DragFloat("Quadratic", &quadratic);
        ImGui::DragFloat("CutOff", &cutOff);
        ImGui::DragFloat("Outer CutOff", &outerCutOff);

        if (color.x != colorf[0] || color.y != colorf[1] || color.z != colorf[2] || color.w != colorf[3])
        {
            light->SetColor(Forge::Color(colorf[0], colorf[1], colorf[2], colorf[3]));
        }

        if (linear != light->Linear())
        {
            light->Linear(linear);
        }

        if (quadratic != light->Quadratic())
        {
            light->Quadratic(quadratic);
        }

        if (cutOff != light->CutOff())
        {
            light->CutOff(cutOff);
        }

        if (outerCutOff != light->OuterCutOff())
        {
            light->OuterCutOff(outerCutOff);
        }
    }

    inline void DrawComponent(Forge::DirectionalLightComponent* component)
    {
        Forge::DirectionalLight* light = component->GetLight();
        Forge::Vector4 color = light->GetColor().GetNormalizedVector();
        Forge::Vector3 direction = light->Direction();

        float colorf[4] = { color.x, color.y, color.z, color.w };
        float dir[3] = { direction.x, direction.y, direction.z };

        ImGui::ColorEdit4("Light color", colorf);
        ImGui::DragFloat3("Direction", dir);

        if (color.x != colorf[0] || color.y != colorf[1] || color.z != colorf[2] || color.w != colorf[3])
        {
            light->SetColor(Forge::Color(colorf[0], colorf[1], colorf[2], colorf[3]));
        }

        if (direction.x != dir[0] || direction.y != dir[1] || direction.z != dir[2])
        {
            light->Direction(Forge::Vector3(dir[0], dir[1], dir[2]));
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

        if (typeid(*component) == typeid(Forge::ModelRenderer))
        {
            if (ImGui::CollapsingHeader("Model Renderer"))
            {
                Forge::ModelRenderer* rend = static_cast<Forge::ModelRenderer*>(component);
                DrawComponent(rend);
            }
        }

        if (typeid(*component) == typeid(Forge::PointLightComponent))
        {
            if (ImGui::CollapsingHeader("Light Component"))
            {
                Forge::PointLightComponent* rend = static_cast<Forge::PointLightComponent*>(component);
                DrawComponent(rend);
            }
        }

        if (typeid(*component) == typeid(Forge::SpotLightComponent))
        {
            if (ImGui::CollapsingHeader("Light Component"))
            {
                Forge::SpotLightComponent* rend = static_cast<Forge::SpotLightComponent*>(component);
                DrawComponent(rend);
            }
        }

        if (typeid(*component) == typeid(Forge::DirectionalLightComponent))
        {
            if (ImGui::CollapsingHeader("Light Component"))
            {
                Forge::DirectionalLightComponent* rend = static_cast<Forge::DirectionalLightComponent*>(component);
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
				if(ImGui::Button("Transform"))
				{
					entity->AddComponent<Forge::TransformComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::Button("Sprite"))
				{
					entity->AddComponent<Forge::SpriteRenderer>();
					ImGui::CloseCurrentPopup();
				}

                if (ImGui::Button("Model"))
                {
                    entity->AddComponent<Forge::ModelRenderer>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("Point Light"))
                {
                    entity->AddComponent<Forge::PointLightComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("Spot Light"))
                {
                    entity->AddComponent<Forge::SpotLightComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("Directional Light"))
                {
                    entity->AddComponent<Forge::DirectionalLightComponent>();
                    ImGui::CloseCurrentPopup();
                }
				
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}
