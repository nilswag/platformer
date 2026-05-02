#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera()
		: m_view(1.0f) {
	}

	inline void move(const glm::vec2& pos)
	{
		m_view = glm::translate(m_view, glm::vec3(pos, 1.0f));
	}

	inline const glm::mat4& view() const { return m_view; }
private:
	glm::mat4 m_view;
};