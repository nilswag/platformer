#include <string_view>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/log.h"
#include "window.h"

void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	instance->m_width = width;
	instance->m_height = height;
	glViewport(0, 0, width, height);

	log().debug("Window", "Resized to ({}, {})", width, height);
}

Window::Window(int width, int height, std::string_view title)
	:m_width(width), m_height(height), m_window(nullptr)
{
	if (!glfwInit())
		log().fatal("Window", "Failed to initialize glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, title.data(), nullptr, nullptr);
	if (!m_window)
		log().fatal("Window", "Failed to initialize glfw window");
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		log().fatal("Window", "Failed to initialize glad");

	log().info("Window", "GL Version : {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	log().info("Window", "GL Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	log().info("Window", "GL Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
	glViewport(0, 0, m_width, m_height);

	log().debug("Window", "Initialized ({}x{})", m_width, m_height);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
	log().debug("Window", "Deinitialized");
}