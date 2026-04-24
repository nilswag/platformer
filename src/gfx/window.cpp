#include <chrono>
#include <glad/glad.h>
#include "window.h"
#include "util/log.h"

void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window& instance = Window::getInstance();
	instance.m_width = width;
	instance.m_height = height;
	glViewport(0, 0, width, height);

	logger::debug("Window resized to ({}, {}).", width, height);
}

Window& Window::getInstance()
{
	static Window instance;
	return instance;
}

Window::Window()
	: m_width(800), m_height(800), m_title("platformer"), m_window(nullptr), m_dt(0.0)
{
	if (!glfwInit())
		logger::fatal("Failed to initialize glfw.");
	logger::trace("Glfw initialized.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
	if (!m_window)
		logger::fatal("Failed to initialize glfw window.");
	logger::trace("Window initialized.");
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		logger::fatal("Failed to initialize glad.");
	logger::trace("Glad initialized.");

	logger::info("GL Version: {}", (char*)glGetString(GL_VERSION));
	logger::info("GL Vendor: {}", (char*)glGetString(GL_VENDOR));
	logger::info("GL Renderer: {}", (char*)glGetString(GL_RENDERER));

	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
	glViewport(0, 0, m_width, m_height);

	logger::debug("Window initialized.");
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
	logger::debug("Window deinitialized.");
}

void Window::loop()
{
	logger::debug("Main loop started.");

	auto last = std::chrono::high_resolution_clock::now();
	double timer = 0.0;

	while (!glfwWindowShouldClose(m_window))
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = last - now;
		last = now;
		m_dt = duration.count();

		glfwPollEvents();
		
		timer += m_dt;
		logger::info("{}", timer);
	}
}