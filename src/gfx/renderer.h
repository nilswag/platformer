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
		: m_x(x), m_y(y), m_width(width), m_height(height), m_color(color)
	{ }
}; 

class Renderer
{
public:
	Renderer();
	~Renderer() = default;

	Renderer(const Renderer&) = delete;
	void operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	void operator=(Renderer&&) = delete;

	inline void renderQuad(Quad& quad) { renderQuad(quad.m_x, quad.m_y, quad.m_width, quad.m_height, quad.m_color); };
	void renderQuad(float x, float y, float width, float height, Color color = WHITE);

private:
	enum class ShaderType
	{
		BASIC = 0,
		N
	};

	std::array<std::unique_ptr<Shader>, (size_t)ShaderType::N> m_shaders;
};