#pragma once
#include "gfx/window.h"
#include "gfx/renderer.h"

class App
{
public:
	App();
	~App() = default;

	App(const App&) = delete;
	void operator=(const App&) = delete;

	App(App&&) = delete;
	void operator=(App&&) = delete;

	void run();

private:
	Window m_window;
	Renderer m_renderer;
};