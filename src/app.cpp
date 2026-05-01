#include <glad/glad.h>
#include <glm/glm.hpp>
#include <chrono>
#include <cmath>

#include "util/log.h"
#include "app.h"
#include "gfx/renderer.h"

App::App()
	: m_window(800, 800, "platformer"), m_renderer(m_window), m_dt(0.0f)
{ }

void App::run()
{
	log().debug("App", "Loop start");

	glm::vec2 pos(0.0f, 0.0f);

	float timer = 0.0f;
	float sum = 0.0f;
	int count = 0;

	auto last = std::chrono::high_resolution_clock::now();
	while (!m_window.shouldClose())
	{
		auto now = std::chrono::high_resolution_clock::now();
		m_dt = std::chrono::duration<float>(now - last).count();
		last = now;

		timer += m_dt;
		sum += m_dt;
		count++;
		if (timer >= 1.0f)
		{
			timer = 0.0f;
			float avgDt = sum / count;
			float avgFps = 1.0f / avgDt;
			sum = 0.0f;

			log().info("App", "AVG FPS: {:<8} | AVG DT: {}ms", std::round(avgFps * 1e2f) / 1e2f, std::round(avgDt * 1e5f) / 1e2f);
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float vel = 200.0f * m_dt;
	
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