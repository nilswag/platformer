#include <glad/glad.h>
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

	m_shaders[(size_t)ShaderType::QUAD] = std::make_unique<Shader>(
		shaders::quad::vertex, shaders::quad::fragment
	);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::renderQuad(Quad& quad)
{

}

void Renderer::renderQuad(float x, float y, float width, float height, Color color)
{

}