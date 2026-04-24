#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const Window&) = delete;
	void operator=(const Window&) = delete;
	~Window();

	static Window& getInstance();

	void loop();

private:
	Window();

	GLFWwindow* window;
	int width, height;
	const char* title;
};