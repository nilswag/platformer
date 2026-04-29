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

	enum class ShaderType
	{
		BASIC = 0,
		N
	};

	inline Shader* getShader(ShaderType type) const
	{
		int index = static_cast<int>(type);
		if (index < 0 || index >= m_shaders.size())
		{
			log().err("Renderer", "Invalid shader type: {}", static_cast<int>(type));
			return nullptr;
		}

		return m_shaders[index].get();
	}

	inline void renderQuad(Quad& quad) { renderQuad(quad.m_x, quad.m_y, quad.m_width, quad.m_height, quad.m_color); };

	void renderQuad(float x, float y, float width, float height, Color color = WHITE);

private:
	std::array<std::unique_ptr<Shader>, static_cast<int>(ShaderType::N)> m_shaders;
	std::array<unsigned int, static_cast<int>(ShaderType::N)> m_vaos;
};