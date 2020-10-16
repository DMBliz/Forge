#include "imgui_impl.h"
#include "include/glad/glad.h"
#include "Core/Engine.h"
#if defined(_WIN32)
#include "Platform/Windows/WindowWin32.h"
#endif
#include "Utilities/Timer.h"

// Data
static double       g_Time = 0.0f;
static bool         g_MouseJustPressed[3] = { false, false, false };
static float        g_MouseWheel = 0.0f;
static GLuint       g_FontTexture = 0;
static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;


static const char* ImGui_GetClipboardText(void* user_data)
{
	return Forge::engine->GetWindow()->GetClipboard().CString();
}

static void ImGui_SetClipboardText(void* /*user_data*/, const char* text)
{
	Forge::engine->GetWindow()->SetClipboard(text);
}

void ImGui_RenderDrawLists(ImDrawData* draw_data)
{
	// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
	ImGuiIO& io = ImGui::GetIO();
	int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0)
		return;
	draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	// Backup GL state
	GLenum last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture);
	glActiveTexture(GL_TEXTURE0);
	GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	GLint last_sampler; glGetIntegerv(GL_SAMPLER_BINDING, &last_sampler);
	GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
	GLint last_element_array_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
	GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
	GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
	GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
	GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
	GLenum last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
	GLenum last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
	GLenum last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
	GLenum last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
	GLenum last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
	GLenum last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
	GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
	GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
	GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

	// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Setup viewport, orthographic projection matrix
	glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
	const float ortho_projection[4][4] =
	{
		{ 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
		{ 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
		{ 0.0f,                  0.0f,                  -1.0f, 0.0f },
		{ -1.0f,                  1.0f,                   0.0f, 1.0f },
	};
	glUseProgram(g_ShaderHandle);
	glUniform1i(g_AttribLocationTex, 0);
	glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
	glBindVertexArray(g_VaoHandle);
	glBindSampler(0, 0); // Rely on combined texture/sampler state.

	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawIdx* idx_buffer_offset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
				glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
			}
			idx_buffer_offset += pcmd->ElemCount;
		}
	}

	// Restore modified GL state
	glUseProgram(last_program);
	glBindTexture(GL_TEXTURE_2D, last_texture);
	glBindSampler(0, last_sampler);
	glActiveTexture(last_active_texture);
	glBindVertexArray(last_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
	glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
	glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
	if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
	if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
	if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
	if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, last_polygon_mode[0]);
	glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
	glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}

bool ImGui_Init(Forge::Window* window, bool install_callbacks)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab] = static_cast<int>(Forge::KeyboardKey::Tab);                         // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
	io.KeyMap[ImGuiKey_LeftArrow] = static_cast<int>(Forge::KeyboardKey::Left);
	io.KeyMap[ImGuiKey_RightArrow] = static_cast<int>(Forge::KeyboardKey::Right);
	io.KeyMap[ImGuiKey_UpArrow] = static_cast<int>(Forge::KeyboardKey::Up);
	io.KeyMap[ImGuiKey_DownArrow] = static_cast<int>(Forge::KeyboardKey::Down);
	io.KeyMap[ImGuiKey_PageUp] = static_cast<int>(Forge::KeyboardKey::PageUp);
	io.KeyMap[ImGuiKey_PageDown] = static_cast<int>(Forge::KeyboardKey::PageDown);
	io.KeyMap[ImGuiKey_Home] = static_cast<int>(Forge::KeyboardKey::Home);
	io.KeyMap[ImGuiKey_End] = static_cast<int>(Forge::KeyboardKey::End);
	io.KeyMap[ImGuiKey_Delete] = static_cast<int>(Forge::KeyboardKey::Delete);
	io.KeyMap[ImGuiKey_Backspace] = static_cast<int>(Forge::KeyboardKey::Backspace);
	io.KeyMap[ImGuiKey_Enter] = static_cast<int>(Forge::KeyboardKey::Return);
	io.KeyMap[ImGuiKey_Escape] = static_cast<int>(Forge::KeyboardKey::Escape);
	io.KeyMap[ImGuiKey_A] = static_cast<int>(Forge::KeyboardKey::A);
	io.KeyMap[ImGuiKey_C] = static_cast<int>(Forge::KeyboardKey::C);
	io.KeyMap[ImGuiKey_V] = static_cast<int>(Forge::KeyboardKey::V);
	io.KeyMap[ImGuiKey_X] = static_cast<int>(Forge::KeyboardKey::X);
	io.KeyMap[ImGuiKey_Y] = static_cast<int>(Forge::KeyboardKey::Y);
	io.KeyMap[ImGuiKey_Z] = static_cast<int>(Forge::KeyboardKey::Z);

	io.RenderDrawListsFn = ImGui_RenderDrawLists;       // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
	io.SetClipboardTextFn = ImGui_SetClipboardText;
	io.GetClipboardTextFn = ImGui_GetClipboardText;
	io.ClipboardUserData = nullptr;
#ifdef _WIN32
	io.ImeWindowHandle = static_cast<Forge::WindowWin32*>(window)->GetNativeWindow();
#endif

	if (install_callbacks)
	{
		Forge::engine->GetInputSystem()->onMouseButtonStateChanged.Add<&ImGui_MouseButtonCallback>();
		Forge::engine->GetInputSystem()->onMouseWheelScroll.Add<&ImGui_ScrollCallback>();
		Forge::engine->GetInputSystem()->onKeyStateChanged.Add<&ImGui_KeyCallback>();
		Forge::engine->GetInputSystem()->onCharacterPressed.Add<&ImGui_CharCallback>();
	}

	return true;
}

void ImGui_Shutdown()
{
	ImGui_InvalidateDeviceObjects();
	ImGui::Shutdown();
}

void ImGui_NewFrame()
{
	if (!g_FontTexture)
		ImGui_CreateDeviceObjects();

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	Forge::Vector2i winSize = Forge::engine->GetWindow()->GetSize();
	Forge::Vector2i frameSize = Forge::engine->GetWindow()->GetSize();

	io.DisplaySize = ImVec2((float)winSize.x, (float)winSize.y);
	io.DisplayFramebufferScale = ImVec2(winSize.x > 0 ? ((float)frameSize.x / winSize.x) : 0, winSize.y > 0 ? ((float)frameSize.y / winSize.y) : 0);

	// Setup time step
	double current_time = Forge::Timer::Time();
	io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
	g_Time = current_time;

	// Setup inputs
	// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
	if (Forge::engine->GetWindow()->IsFocused())
	{
		if (io.WantMoveMouse)
		{
			Forge::engine->GetInputSystem()->SetMousePosition(Forge::Vector2(io.MousePos.x, io.MousePos.y));
			// Set mouse position if requested by io.WantMoveMouse flag (used when io.NavMovesTrue is enabled by user and using directional navigation)
		}
		else
		{
			Forge::Vector2 pos = Forge::engine->GetInputSystem()->GetCursorPosition();
			io.MousePos = ImVec2(pos.x, pos.y);   // Get mouse position in screen coordinates (set to -1,-1 if no mouse / on another screen, etc.)
		}
	}
	else
	{
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	}

	for (int i = 0; i < 3; i++)
	{
		// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
		io.MouseDown[i] = g_MouseJustPressed[i] || Forge::engine->GetInputSystem()->GetMouseButtonState(static_cast<Forge::MouseButton>(i)) != Forge::InputState::None;
		g_MouseJustPressed[i] = false;
	}

	io.MouseWheel = g_MouseWheel;
	g_MouseWheel = 0.0f;

	// Hide OS mouse cursor if ImGui is drawing it
	//glfwSetInputMode(g_Window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

	// Start the frame. This call will update the io.WantCaptureMouse, io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not) to your application.
	ImGui::NewFrame();
}

void ImGui_InvalidateDeviceObjects()
{
	if (g_VaoHandle) glDeleteVertexArrays(1, &g_VaoHandle);
	if (g_VboHandle) glDeleteBuffers(1, &g_VboHandle);
	if (g_ElementsHandle) glDeleteBuffers(1, &g_ElementsHandle);
	g_VaoHandle = g_VboHandle = g_ElementsHandle = 0;

	if (g_ShaderHandle && g_VertHandle) glDetachShader(g_ShaderHandle, g_VertHandle);
	if (g_VertHandle) glDeleteShader(g_VertHandle);
	g_VertHandle = 0;

	if (g_ShaderHandle && g_FragHandle) glDetachShader(g_ShaderHandle, g_FragHandle);
	if (g_FragHandle) glDeleteShader(g_FragHandle);
	g_FragHandle = 0;

	if (g_ShaderHandle) glDeleteProgram(g_ShaderHandle);
	g_ShaderHandle = 0;

	if (g_FontTexture)
	{
		glDeleteTextures(1, &g_FontTexture);
		ImGui::GetIO().Fonts->TexID = 0;
		g_FontTexture = 0;
	}
}

bool ImGui_CreateFontsTexture()
{
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

															  // Upload texture to graphics system
	GLint last_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glGenTextures(1, &g_FontTexture);
	glBindTexture(GL_TEXTURE_2D, g_FontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// Store our identifier
	io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

	// Restore state
	glBindTexture(GL_TEXTURE_2D, last_texture);

	return true;
}

bool ImGui_CreateDeviceObjects()
{
	// Backup GL state
	GLint last_texture, last_array_buffer, last_vertex_array;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

	const GLchar *vertex_shader =
		"#version 330\n"
		"uniform mat4 ProjMtx;\n"
		"in vec2 Position;\n"
		"in vec2 UV;\n"
		"in vec4 Color;\n"
		"out vec2 Frag_UV;\n"
		"out vec4 Frag_Color;\n"
		"void main()\n"
		"{\n"
		"	Frag_UV = UV;\n"
		"	Frag_Color = Color;\n"
		"	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
		"}\n";

	const GLchar* fragment_shader =
		"#version 330\n"
		"uniform sampler2D Texture;\n"
		"in vec2 Frag_UV;\n"
		"in vec4 Frag_Color;\n"
		"out vec4 Out_Color;\n"
		"void main()\n"
		"{\n"
		"	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
		"}\n";

	g_ShaderHandle = glCreateProgram();
	g_VertHandle = glCreateShader(GL_VERTEX_SHADER);
	g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(g_VertHandle, 1, &vertex_shader, 0);
	glShaderSource(g_FragHandle, 1, &fragment_shader, 0);
	glCompileShader(g_VertHandle);
	glCompileShader(g_FragHandle);
	glAttachShader(g_ShaderHandle, g_VertHandle);
	glAttachShader(g_ShaderHandle, g_FragHandle);
	glLinkProgram(g_ShaderHandle);

	g_AttribLocationTex = glGetUniformLocation(g_ShaderHandle, "Texture");
	g_AttribLocationProjMtx = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
	g_AttribLocationPosition = glGetAttribLocation(g_ShaderHandle, "Position");
	g_AttribLocationUV = glGetAttribLocation(g_ShaderHandle, "UV");
	g_AttribLocationColor = glGetAttribLocation(g_ShaderHandle, "Color");

	glGenBuffers(1, &g_VboHandle);
	glGenBuffers(1, &g_ElementsHandle);

	glGenVertexArrays(1, &g_VaoHandle);
	glBindVertexArray(g_VaoHandle);
	glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
	glEnableVertexAttribArray(g_AttribLocationPosition);
	glEnableVertexAttribArray(g_AttribLocationUV);
	glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
	glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
	glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

	ImGui_CreateFontsTexture();

	// Restore modified GL state
	glBindTexture(GL_TEXTURE_2D, last_texture);
	glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
	glBindVertexArray(last_vertex_array);

	return true;
}

void ImGui_MouseButtonCallback(Forge::MouseButton button, Forge::InputState state)
{
	if(state==Forge::InputState::Down && button == Forge::MouseButton::Left || button == Forge::MouseButton::Right || button == Forge::MouseButton::Middle)
	{
		g_MouseJustPressed[static_cast<int>(button)] = true;
	}
}

void ImGui_ScrollCallback(const Forge::Vector2& scroll)
{
	g_MouseWheel += scroll.y;
}

void ImGui_KeyCallback(Forge::KeyboardKey key, Forge::InputState state)
{
	ImGuiIO& io = ImGui::GetIO();

	if (state == Forge::InputState::Down)
		io.KeysDown[static_cast<int>(key)] = true;
	if (state == Forge::InputState::Up)
		io.KeysDown[static_cast<int>(key)] = false;

	io.KeyCtrl = io.KeysDown[static_cast<int>(Forge::KeyboardKey::LeftControl)] || io.KeysDown[static_cast<int>(Forge::KeyboardKey::RightControl)];
	io.KeyShift = io.KeysDown[static_cast<int>(Forge::KeyboardKey::LeftShift)] || io.KeysDown[static_cast<int>(Forge::KeyboardKey::RightShift)];
	io.KeyAlt = io.KeysDown[static_cast<int>(Forge::KeyboardKey::LeftAlt)] || io.KeysDown[static_cast<int>(Forge::KeyboardKey::RightAlt)];
	io.KeySuper = io.KeysDown[static_cast<int>(Forge::KeyboardKey::LeftSystem)] || io.KeysDown[static_cast<int>(Forge::KeyboardKey::RightSystem)];
}

void ImGui_CharCallback(uint c)
{
	ImGuiIO& io = ImGui::GetIO();
	if (c > 0 && c < 0x10000)
		io.AddInputCharacter(static_cast<unsigned short>(c));
}


