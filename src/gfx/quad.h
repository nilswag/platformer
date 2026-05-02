#pragma once
#include <glm/glm.hpp>

struct Quad
{
	Quad(const glm::vec2& pos, const glm::vec2& size)
		: m_pos(pos), m_size(size), m_rot(0.0f), m_color(1.0f, 1.0f, 1.0f, 1.0f)
	{
	}

	Quad(const glm::vec2& pos, const glm::vec2& size, float rot)
		: m_pos(pos), m_size(size), m_rot(rot), m_color(1.0f, 1.0f, 1.0f, 1.0f)
	{
	}

	Quad(const glm::vec2& pos, const glm::vec2& size, float rot, glm::vec4 color)
		: m_pos(pos), m_size(size), m_rot(rot), m_color(color)
	{
	}

	glm::vec2 m_pos;
	glm::vec2 m_size;
	float m_rot;
	glm::vec4 m_color;
};