#include <glad/glad.h>
#include "window.h"
#include "util/log.h"

Window::Window(int width, int height, const char* title)
	: width(width), height(height), title(title), window(nullptr), dt(0.0)
{
	if (!glfwInit())
		logger::fatal("Failed to initialize glfw.");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
		logger::fatal("Failed to initialize glfw window.");
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		logger::fatal("Failed to initialize glad.");

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