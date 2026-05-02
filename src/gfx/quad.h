#pragma once
#include <glm/glm.hpp>

struct Quad
{
	Quad(const glm::vec2& pos, const glm::vec2& size)
		: Quad(pos, size, 0.0f)
	{ }

	Quad(const glm::vec2& pos, const glm::vec2& size, float rot)
		: Quad(pos, size, rot, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
	{ }

	Quad(const glm::vec2& pos, const glm::vec2& size, float rot, glm::vec4 color)
		:  m_color(color)
	{
		m_model = glm::mat4(1.0f);
		m_model = glm::translate(m_model, glm::vec3(pos, 0.0f));
		m_model = glm::rotate(m_model, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
		m_model = glm::scale(m_model, glm::vec3(size, 1.0f));
	}

	glm::mat4 m_model;
	glm::vec4 m_color;
};