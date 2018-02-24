// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)
#define GLFW_EXPOSE_NATIVE_WIN32
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

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 frameBuffer_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float windowWidth = 0;
	float windowHeight = 0;

	ImVec2 windowSize;

	

	ForgeEditor::ress = eng.GetFileSystem()->GetFilesFromDirectory("Resources/");
	eng.GetResources()->LoadAll(ForgeEditor::ress);
	eng.Update();
	Forge::ResourceManager<Forge::Shader>* mn = eng.GetResources()->GetResourceManager<Forge::Shader>();
	auto* rs = mn->GetAll();
	for(auto it = rs->begin(); it != rs->end(); ++it)
	{
		it._Ptr->_Myval.second->Compile();
	}
	while (Forge::engine->IsActive())
	{
		bool leftPressed = Forge::engine->GetInputSystem()->GetMouseButtonState(Forge::MouseButton::Left) == Forge::InputState::Hold;
		bool rightPressed = Forge::engine->GetInputSystem()->GetMouseButtonState(Forge::MouseButton::Right) == Forge::InputState::Hold;
		bool middlePressed = Forge::engine->GetInputSystem()->GetMouseButtonState(Forge::MouseButton::Middle) == Forge::InputState::Hold;
		
		eng.Update();
		ImGui_NewFrame();
		
		clear_color.x = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedR();
		clear_color.y = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedG();
		clear_color.z = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedB();
		clear_color.w = Forge::engine->GetRenderer()->GetWindowClearColor().NormalizedB();

		{
			ImVec2 mousePo = ImGui::GetMousePos();
			Forge::Vector2 pos = Forge::engine->GetInputSystem()->GetCursorPosition();
			float* mfg = new float[2]{ pos.x, pos.y };
			float* mf = new float[2]{ mousePo.x,mousePo.y };
			static float *fv = new float[3]{ 1.0f, 2.0f, 3.0f };
			ImGui::DragFloat3("test", fv);
			static float f = 0.0f;
			ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
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

			if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
				show_demo_window ^= 1;
			if (ImGui::Button("Another Window"))
				show_another_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::DragFloat2("Forge mouse position", mfg);
			ImGui::DragFloat2("ImGui mouse position", mf);

			
		}
		
		ForgeEditor::Update();

		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		ImGui::Render();
	}

	Forge::engine->ShutDown();

	return 0;
}
