#include <iostream>
#include <GLFW/glfw3.h>
#include "window.h"
#include "../util/log.h"

Window::Window(int width, int height, const char* title)
	: handle(nullptr), width(width), height(height), title(title)
{
	if (!glfwInit()) logger::fatal("Unable to initialize glfw.");
}

Window::~Window()
{

}