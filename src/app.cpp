#include <chrono>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "app.h"

App::App()
	: m_window(1280, 720, "platformer"), m_dt(0.0f)
{ }

void App::run()
{
	float timer = 0.0f;
	float sum = 0.0f;
	int count = 0;

	auto last = std::chrono::high_resolution_clock::now();
	while (!m_window.shouldClose())
	{
		auto first = std::chrono::high_resolution_clock::now();
		m_dt = std::chrono::duration<float>(first - last).count();
		last = first;

		timer += m_dt;
		sum += m_dt;
		count++;

		if (timer >= 1.0f)
		{
			float avgDt = sum / count;
			float avgFps = 1.0f / avgDt;
			spdlog::info("Avg fps: {:<6.1f} | Avg dt: {:.2f}ms", avgFps, avgDt * 1e3);

			sum = 0.0f;
			count = 0;
			timer -= 1.0f;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_window.swapBuffers();
		m_window.pollEvents();
	}
}