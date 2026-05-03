#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	inline void swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	inline void pollEvents()
	{
		glfwPollEvents();
	}

	inline int getWidth() const
	{
		return m_width;
	}

	inline int getHeight() const
	{
		return m_height;
	}

	inline bool shouldClose() const
	{
		return glfwWindowShouldClose(m_window);
	}

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	int m_width, m_height;
	GLFWwindow* m_window;
};