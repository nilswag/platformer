#pragma once
#include "gfx/window.h"
#include "gfx/renderer.h"

class App
{
public:
	App();

	void run();

	inline float getDt() const
	{
		return m_dt;
	}

private:
	Window m_window;
	Renderer m_renderer;
	float m_dt;
};