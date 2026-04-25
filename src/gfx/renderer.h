#pragma once
#include <array>
#include <memory>
#include "shader.h"

using Color = std::array<float, 4>;
static constexpr Color WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

struct Quad
{
	float m_x, m_y;
	float m_width, m_height;
	std::array<float, 4> m_color;

	Quad(float x, float y, float width, float height, Color color = WHITE)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_color = color;
	}
}; 

class Renderer
{

public:
	Renderer(const Renderer&) = delete;
	void operator=(const Renderer&) = delete;

	static Renderer& getInstance();

	void renderQuad(Quad& quad);
	void renderQuad(float x, float y, float width, float height, Color color = WHITE);

private:
	Renderer();

	enum class ShaderType
	{
		QUAD = 0,
		N
	};

	std::array<std::unique_ptr<Shader>, (size_t)ShaderType::N> m_shaders;

};