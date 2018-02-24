#pragma once
#include "Scene/Scene.h"
#include "imgui/imgui.h"


namespace ForgeEditor
{
	Forge::Entity* selectedEntity = nullptr;

	inline void DrawHierarchy(Forge::Entity* entity)
	{
		static int selection_mask = (1 << 2); 
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());
		std::vector<Forge::Entity*> entityes = entity->GetAllChilds();
		for (int i = 0; i < entityes.size(); i++)
		{

			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow;
			if(selectedEntity != nullptr && selectedEntity->GetEntityID() == entityes[i]->GetEntityID())
			{
				node_flags |= ((selection_mask & (1 << entityes[i]->GetEntityID())) ? ImGuiTreeNodeFlags_Selected : 0);
			}
			if (entityes[i]->GetChildsCount() > 0)
			{
				bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)entityes[i]->GetEntityID(), node_flags, entityes[i]->Name().CString());
				if (ImGui::IsItemClicked() || ImGui::IsItemClicked(1))
				{
					selectedEntity = entityes[i];
				}
				if (node_open)
				{
					DrawHierarchy(entityes[i]);
					ImGui::TreePop();
				}
			}else
			{
				node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				ImGui::TreeNodeEx((void*)(intptr_t)entityes[i]->GetEntityID(), node_flags, entityes[i]->Name().CString());
				if (ImGui::IsItemClicked() || ImGui::IsItemClicked(1))
				{
					selectedEntity = entityes[i];
				}
			}
		}

		if (selectedEntity != nullptr)
		{
			if (ImGui::GetIO().KeyCtrl)
				selection_mask ^= (1 << selectedEntity->GetEntityID());
			else 
				selection_mask = (1 << selectedEntity->GetEntityID());
		}

		ImGui::PopStyleVar();
	}

	inline void DrawHierarchy(bool& draw, Forge::Scene* scene)
	{
		ImGui::Begin("Hierarchy", &draw);
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0) || ImGui::IsMouseClicked(1))
		{
			selectedEntity = nullptr;
		}
		DrawHierarchy(scene);
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1))
		{
			ImGui::OpenPopup("HierarchyPopUp");
		}

		if (ImGui::BeginPopup("HierarchyPopUp"))
		{
			if (ImGui::Button("Create entity"))
			{
				auto tmp = Forge::engine->GetScene()->CreateEntity<Forge::Entity>("Game Object");

				if (selectedEntity != nullptr)
				{
					tmp->SetParent(selectedEntity);
				}
				ImGui::CloseCurrentPopup();
			}
			if (selectedEntity != nullptr)
			{
				if (ImGui::Button("Delete entity"))
				{
					Forge::engine->GetScene()->DestroyEntity(selectedEntity);
					selectedEntity = nullptr;
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}
