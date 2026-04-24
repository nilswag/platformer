#include <glad/glad.h>
#include "window.h"
#include "util/log.h"

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