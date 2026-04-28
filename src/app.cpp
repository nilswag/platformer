#include <glad/glad.h>

#include "util/log.h"
#include "app.h"

App::App()
	: m_window(800, 800, "platformer")
{ }

void App::run()
{
	log().debug("App", "Loop start");

	while (!m_window.shouldClose())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_window.update();
	}

	log().debug("App", "Loop end");
}