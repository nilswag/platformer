#pragma once
#include <array>
#include <memory>
#include <glm/glm.hpp>

#include "shader.h"

constexpr glm::vec4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);

constexpr glm::vec3 ROT_DIR = glm::vec3(0.0f, 0.0f, 1.0f);

struct Quad
{
	float m_x, m_y;
	float m_width, m_height;
	float m_rot;
	glm::vec4 m_color;

	Quad(float x, float y, float width, float height, float rot, glm::vec4 color = WHITE)
		: m_x(x), m_y(y), m_width(width), m_height(height), m_rot(rot), m_color(color)
	{ }
}; 

class Camera
{
public:
	Camera(int x, int y)
		: m_view(glm::mat4(1.0f))
	{ transform(x, y); lookAt(glm::vec2(0.0f, 0.0f)); }
	~Camera() = default;

	inline void lookAt(const glm::vec2& target)
	{
		m_view = glm::lookAt(m_pos, glm::vec3(target, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	inline void transform(float x, float y, float rot = 0.0f)
	{
		m_view = glm::translate(m_view, glm::vec3(x, y, 0.0f));
		m_view = glm::rotate(m_view, glm::radians(rot), ROT_DIR);
	}

	inline const glm::mat4& view() const { return m_view; }
private:
	glm::vec3 m_pos;
	glm::mat4 m_view;
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

	inline void renderQuad(Quad& quad) { renderQuad(quad.m_x, quad.m_y, quad.m_width, quad.m_height, quad.m_rot, quad.m_color); };
	inline Camera& camera() { return m_camera; }

	void renderQuad(float x, float y, float width, float height, float rot, const glm::vec4& color = WHITE);

private:
	std::array<std::unique_ptr<Shader>, static_cast<int>(ShaderType::N)> m_shaders;
	std::array<unsigned int, static_cast<int>(ShaderType::N)> m_vaos;
	Camera m_camera;
};