// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)
#include "imgui/imgui.h"
#include "imgui_impl.h"
#include <stdio.h>
#include "imgui/imgui_internal.h"
#include "Controls/GUIScene.h"
#include "Controls/GUIEditor.h"
#include <filesystem>
#include "Resources/Resources.h"
#include "Controls/GUIResources.h"


int main(int, char**)
{
	Forge::Engine eng;
	eng.Init();
	eng.OpenWindow(Forge::Vector2i(1280, 720), "Forge Engine", false, false);
	eng.GetRenderer()->SetSize(Forge::Vector2i(800, 600));
	eng.GetRenderer()->RenderToScreen(false);

	ImGui_Init(eng.GetWindow(), true);

	ImGui::StyleColorsClassic();

	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 frameBuffer_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	

	ForgeEditor::ress = eng.GetFileSystem()->GetFilesFromDirectory("Resources/");
	eng.GetResources()->LoadAll(ForgeEditor::ress);
	eng.GetResources()->Update();
	Forge::ResourceManager<Forge::Shader>* mn = eng.GetResources()->GetResourceManager<Forge::Shader>();
	auto* rs = mn->GetAll();
	for(auto it = rs->begin(); it != rs->end(); ++it)
	{
        it->second->Compile();
	}

	while (Forge::engine->IsActive())
	{
		
		eng.Update();
		ImGui_NewFrame();
		
		clear_color.x = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedR();
		clear_color.y = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedG();
		clear_color.z = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedB();
		clear_color.w = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedB();

		{
			ImVec4 prevClearColor = clear_color;
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
			if(prevClearColor.x != clear_color.x || prevClearColor.y != clear_color.y || prevClearColor.z != clear_color.z || prevClearColor.w != clear_color.w)
			{
				Forge::engine->GetRenderer()->SetWindowClearColor(Forge::Color(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
			}
			ImVec4 prevFBCC = frameBuffer_clear_color;
			ImGui::ColorEdit3("Framebuffer clear color", reinterpret_cast<float*>(&frameBuffer_clear_color));
			if (prevFBCC.x != frameBuffer_clear_color.x || prevFBCC.y != frameBuffer_clear_color.y || prevFBCC.z != frameBuffer_clear_color.z || prevFBCC.w != frameBuffer_clear_color.w)
			{
				Forge::engine->GetRenderer()->SetFrameBufferClearColor(Forge::Color(frameBuffer_clear_color.x, frameBuffer_clear_color.y, frameBuffer_clear_color.z, frameBuffer_clear_color.w));
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			

			
		}
		
		ForgeEditor::Update();


		ImGui::Render();
	}

	Forge::engine->ShutDown();

	return 0;
}
