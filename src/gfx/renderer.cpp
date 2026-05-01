#include <glad/glad.h>
#include <memory>
#include <glm/glm.hpp>

#include "util/log.h"
#include "renderer.h"
#include "shader.h"

#include "shaders/basic.glsl.hpp"

static float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
};

static int indices[] = {
	0, 1, 2,
	1, 2, 3
};

Renderer::Renderer()
{
	//m_camera.move(glm::vec2(0.5f, 0.0f));

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

void Renderer::renderQuad(const glm::vec2& pos, const glm::vec2& size, float rot, const glm::vec4& color)
{
	for (int i = 0; i < static_cast<int>(ShaderType::N); i++)
	{
		Shader& shader = (*m_shaders[i]);
		shader.use();
		shader.setVec4("color", color);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f));
		model = glm::rotate(model, glm::radians(rot), ROT_DIR);
		model = glm::scale(model, glm::vec3(size, 1.0f));
		shader.setMat4("model", model);

		shader.setMat4("view", m_camera.view());

		glm::mat4 proj(1.0f);
		proj = glm::ortho(0.0f, 500.0f, 0.0f, 500.0f, 1.0f, 0.0f);
		shader.setMat4("proj", proj);

		glBindVertexArray(m_vaos[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}