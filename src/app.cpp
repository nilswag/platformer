#include <glad/glad.h>
#include <glm/glm.hpp>

#include "util/log.h"
#include "app.h"
#include "gfx/renderer.h"

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

		m_renderer.renderQuad(0.0f, 0.0f, 100.0f, 100.0f);

		m_window.update();
	}

	log().debug("App", "Loop end");
}