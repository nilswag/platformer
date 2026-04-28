#include <glad/glad.h>
#include "util/log.h"
#include "renderer.h"
#include "shader.h"

#include "shaders/quad.glsl.hpp"

Renderer& Renderer::getInstance()
{
	static Renderer renderer;
	return renderer;
}

Renderer::Renderer()
{
	float vertices[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	float indices[] = {
		0, 1, 2, 3
	};

	m_shaders[(size_t)ShaderType::BASIC] = std::make_unique<Shader>(
		shaders::quad::vertex, shaders::quad::fragment, "Quad"
	);

	glGenVertexArrays(1, &m_vaoQuad);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	log().debug("Renderer", "Initialized (OpenGL)");
}

void Renderer::renderQuad(Quad& quad)
{
	renderQuad(quad.m_x, quad.m_y, quad.m_width, quad.m_height, quad.m_color);
}

void Renderer::renderQuad(float x, float y, float width, float height, Color color)
{
	for (std::unique_ptr<Shader>& shader : m_shaders)
	{
		(*shader).use();
		glBindVertexArray(m_vaoQuad);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}