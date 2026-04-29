#include <glad/glad.h>

#include "util/log.h"
#include "renderer.h"
#include "shader.h"

#include "shaders/basic.glsl.hpp"

static float vertices[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

static int indices[] = {
	0, 1, 2,
	0, 2, 3
};

Renderer::Renderer()
{
	m_shaders = {
		std::make_unique<Shader>(shaders::basic::vertex, shaders::basic::fragment, "Basic")
	};

	glGenVertexArrays(static_cast<int>(ShaderType::N), m_vaos.data());
	glBindVertexArray(m_vaos[static_cast<int>(ShaderType::BASIC)]);

	unsigned int vbo, ebo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
		
	log().debug("Renderer", "Initialized (OpenGL)");
}

void Renderer::renderQuad(float x, float y, float width, float height, Color color)
{
	for (int i = 0; i < static_cast<int>(ShaderType::N); i++)
	{
		(*m_shaders[i]).use();
		glBindVertexArray(m_vaos[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}