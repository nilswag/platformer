#pragma once
#include <array>
#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "window.h"
#include "shader.h"

static const glm::vec3 ROT_DIR = glm::vec3(0.0f, 0.0f, 1.0f);

class Camera
{
public:
	Camera()
		: m_view(1.0f) { }
	~Camera() = default;

	inline void move(const glm::vec2& pos)
	{
		m_view = glm::translate(m_view, glm::vec3(pos, 1.0f));
	}

	inline const glm::mat4& view() const { return m_view; }
private:
	glm::mat4 m_view;
};

struct Quad
{
	Quad(const glm::vec2& pos, const glm::vec2& size)
		: m_pos(pos), m_size(size), m_rot(0.0f), m_color(1.0f, 1.0f, 1.0f, 1.0f)
	{ }

	Quad(const glm::vec2& pos, const glm::vec2& size, float rot)
		: m_pos(pos), m_size(size), m_rot(rot), m_color(1.0f, 1.0f, 1.0f, 1.0f)
	{
	}

	Quad(const glm::vec2& pos, const glm::vec2& size, float rot, glm::vec4 color)
		: m_pos(pos), m_size(size), m_rot(rot), m_color(color)
	{ }

	glm::vec2 m_pos;
	glm::vec2 m_size;
	float m_rot;
	glm::vec4 m_color;
}; 

class Renderer
{
public:
	Renderer(Window& window);
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

	inline Camera& camera() { return m_camera; }

	void renderQuad(const Quad& quad);

private:
	std::array<std::unique_ptr<Shader>, static_cast<int>(ShaderType::N)> m_shaders;
	std::array<unsigned int, static_cast<int>(ShaderType::N)> m_vaos;
	Window& m_window;
	Camera m_camera;
};