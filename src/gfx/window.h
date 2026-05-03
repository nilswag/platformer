#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	int m_width, m_height;
	GLFWwindow* m_window;
};