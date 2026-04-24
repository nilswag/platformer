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

	double dt();

private:
	Window();
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* window;
	int width, height;
	const char* title;
};