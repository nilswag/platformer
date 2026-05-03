#pragma once
#include "gfx/window.h"

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
	float m_dt;
};