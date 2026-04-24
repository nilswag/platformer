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
	inline double delta() const { return m_dt; }
	inline int width() const { return m_width; }
	inline int height() const { return m_height; }

private:
	Window();
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window;
	int m_width, m_height;
	const char* m_title;
	double m_dt;
};