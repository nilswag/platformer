#pragma once
#include <string_view>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width = 800, int height = 800, std::string_view = "platformer");
	~Window();

	Window(const Window&) = delete;
	void operator=(const Window&) = delete;

	Window(Window&&) = delete;
	void operator=(Window&&) = delete;

	inline void update() const { glfwSwapBuffers(m_window); glfwPollEvents(); }
	inline bool shouldClose() const { return glfwWindowShouldClose(m_window); }
	inline int width() const { return m_width; }
	inline int height() const { return m_height; }
	inline GLFWwindow* handle() const { return m_window; }

private:

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window;
	int m_width, m_height;
};