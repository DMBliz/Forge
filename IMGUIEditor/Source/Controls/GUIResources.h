#pragma once
#include "imgui/imgui.h"
#include "Core/Engine.h"

namespace ForgeEditor
{
	std::vector<Forge::String> ress;
	Forge::String selecetedResource = Forge::String::Empty;

	void DrawFolder(const Forge::String& folderName)
	{
		std::vector<Forge::String> ressInFolder;

		for (const Forge::String& string : ress)
		{
			if(string.Contains(folderName))
			{
				ressInFolder.push_back(string);
			}
		}

		static int selection_mask = (1 << 2);
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());
		Forge::String prevName = Forge::String::Empty;
		for (int i = 0; i < ressInFolder.size(); i++)
		{

			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow;

			uint fn = ressInFolder[i].Find(folderName) + folderName.Length() + 1;
			
			uint lastSL = ressInFolder[i].Find('/', fn);
			if (lastSL != Forge::String::NOTFOUND)
			{
				uint SL = ressInFolder[i].Find('/', lastSL + 1);
				Forge::String name = ressInFolder[i].SubString(fn, lastSL - fn);
				if (prevName != name)
				{
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, name.CString());
					if (ImGui::IsItemClicked())
					{
						selecetedResource = ressInFolder[i];
					}
					if (node_open)
					{
						DrawFolder(name);
						ImGui::TreePop();
					}
				}
				prevName = name;
			}
			else
			{
				if (selecetedResource != Forge::String::Empty && selecetedResource == ressInFolder[i])
				{
					node_flags |= ImGuiTreeNodeFlags_Selected;
				}
				Forge::String name = ressInFolder[i].SubString(fn, ressInFolder[i].Length() - fn);
				node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, name.CString());
				if (ImGui::IsItemClicked())
				{
					selecetedResource = ressInFolder[i];
				}
				prevName = name;
			}
		}


		ImGui::PopStyleVar();
	}

	void DrawResources(bool& drawResources)
	{
		ImGui::Begin("Resources", &drawResources);
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0))
		{
			selecetedResource = Forge::String::Empty;
		}
		DrawFolder("Resources");

		ImGui::End();
	}

}
