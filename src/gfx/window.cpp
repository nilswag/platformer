#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* ptr = static_cast<Window*>(glfwGetWindowUserPointer(window));
	ptr->m_width = width;
	ptr->m_height = height;
	glViewport(0, 0, width, height);

	spdlog::debug("Window resized ({}x{})", width, height);
}

Window::Window(int width, int height, const std::string& title)
	: m_width(width), m_height(height), m_window(nullptr)
{
	if (!glfwInit())
	{
		spdlog::critical("Failed to initialize glfw");
		std::abort();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_window)
	{
		spdlog::critical("Failed to initialize glfw window");
		std::abort();
	}

	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::critical("Failed to initialize glad");
		std::abort();
	}

	glViewport(0, 0, width, height);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

	spdlog::info("Vendor: {}", (char*)glGetString(GL_VENDOR));
	spdlog::info("Renderer: {}", (char*)glGetString(GL_RENDERER));
	spdlog::info("Version: {}", (char*)glGetString(GL_VERSION));

	spdlog::debug("Window initialized ({}x{})", width, height);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}