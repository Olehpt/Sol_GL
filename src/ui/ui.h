#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace UI {
	void InitUI(GLFWwindow* window);
	void NewFrame();
	void Render();
	
	void Sidebar(int w = 100);
}

