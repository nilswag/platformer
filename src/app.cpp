#include <glad/glad.h>
#include <glm/glm.hpp>
#include <chrono>

#include "util/log.h"
#include "app.h"
#include "gfx/renderer.h"

App::App()
	: m_window(800, 800, "platformer")
{ }

void App::run()
{
	log().debug("App", "Loop start");

	glm::vec2 pos(0.0f, 0.0f);

	double timer = 0.0f;
	int count = 0;

	auto last = std::chrono::high_resolution_clock::now();
	while (!m_window.shouldClose())
	{
		auto now = std::chrono::high_resolution_clock::now();
		m_dt = std::chrono::duration<double>(now - last).count();
		last = now;

		timer += m_dt;
		if (timer >= 1.0f)
		{
			timer = 0.0f;

		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float vel = 10.0f * m_dt;
	
		if (glfwGetKey(m_window.handle(), GLFW_KEY_A))
			pos[0] -= vel;
		if (glfwGetKey(m_window.handle(), GLFW_KEY_D))
			pos[0] += vel;
		if (glfwGetKey(m_window.handle(), GLFW_KEY_W))
			pos[1] += vel;
		if (glfwGetKey(m_window.handle(), GLFW_KEY_S))
			pos[1] -= vel;

		m_renderer.renderQuad(pos, glm::vec2(100.0f, 100.0f));

		m_window.update();
	}

	log().debug("App", "Loop end");
}