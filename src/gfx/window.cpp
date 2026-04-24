#include <glad/glad.h>
#include "window.h"
#include "util/log.h"

void Window::frameBufferSizeCallback(GLFWwindow* window, int _width, int _height)
{
	Window& instance = Window::getInstance();
	instance.width = _width;
	instance.height = _height;
	glViewport(0, 0, _width, _height);

	logger::debug("Window resized to ({}, {}).", _width, _height);
}

Window& Window::getInstance()
{
	static Window instance;
	return instance;
}

Window::Window()
	: width(800), height(800), title("platformer"), window(nullptr)
{
	if (!glfwInit())
		logger::fatal("Failed to initialize glfw.");
	logger::trace("Glfw initialized.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
		logger::fatal("Failed to initialize glfw window.");
	logger::trace("Window initialized.");
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		logger::fatal("Failed to initialize glad.");
	logger::trace("Glad initialized.");

	logger::info("GL Version: {}", (char*)glGetString(GL_VERSION));
	logger::info("GL Vendor: {}", (char*)glGetString(GL_VENDOR));
	logger::info("GL Renderer: {}", (char*)glGetString(GL_RENDERER));

	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glViewport(0, 0, width, height);

	logger::debug("Window initialized.");
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	logger::debug("Window deinitialized.");
}

void Window::loop()
{
	logger::debug("Main loop started.");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}