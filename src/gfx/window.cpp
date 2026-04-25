#include <chrono>
#include <cmath>
#include <glad/glad.h>

#include "window.h"
#include "util/log.h"

void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window& instance = Window::getInstance();
	instance.m_width = width;
	instance.m_height = height;
	glViewport(0, 0, width, height);

	logger::debug("Window", "Resized to ({}, {})", width, height);
}

Window& Window::getInstance()
{
	static Window instance;
	return instance;
}

Window::Window()
{
	m_width = 800;
	m_height = 800;
	m_title = "platformer";
	m_window = nullptr;
	m_dt = 0.0;

	if (!glfwInit())
		logger::fatal("Window", "Failed to initialize glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
	if (!m_window)
		logger::fatal("Window", "Failed to initialize glfw window");
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		logger::fatal("Window", "Failed to initialize glad");

	logger::info("Window", "GL Version : {}", (char*)glGetString(GL_VERSION));
	logger::info("Window", "GL Vendor: {}", (char*)glGetString(GL_VENDOR));
	logger::info("Window", "GL Renderer: {}", (char*)glGetString(GL_RENDERER));

	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
	glViewport(0, 0, m_width, m_height);

	logger::debug("Window", "Initialized ({}x{})", m_width, m_height);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
	logger::debug("Window", "Deinitialized");
}

void Window::loop()
{
	logger::trace("Window", "Loop begin");

	auto last = std::chrono::high_resolution_clock::now();
	double timer = 0.0;
	double sum = 0.0;
	long count = 0;

	while (!glfwWindowShouldClose(m_window))
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = now - last;
		last = now;
		m_dt = duration.count();

		glfwPollEvents();
		

		timer += m_dt;
		sum += m_dt;
		count++;

		if (timer >= 1.0)
		{
			timer -= 1.0;
			double avgDt = sum / count;
			count = 0;

			int avgFps = static_cast<int>(1.0 / avgDt);
			double avgMs = avgDt * 1e3;

			logger::info("Window", "AVG FPS: {} | AVG DT: {}ms", avgFps, std::round(avgMs * 100.0) / 100.0);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glfwSwapBuffers(m_window);
	}

	logger::trace("Window", "Loop end");
}