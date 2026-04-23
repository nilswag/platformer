#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	Window() = delete;
	Window(int width, int height, const char* title);
	~Window();
	
private:
	GLFWwindow* handle;
	int width, height;
	const char* title;
};