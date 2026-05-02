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

static const int MAX_INSTANCES = 1024;
static const int INSTANCE_SIZE = sizeof(glm::vec4) + sizeof(glm::mat4);

Pass::Pass(const Shader& shader)
	: m_shader(shader)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * INSTANCE_SIZE, nullptr, GL_DYNAMIC_DRAW);
	
	for (int i = 0; i < 4; i++)
	{
		// model matrix
		glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
		glVertexAttribDivisor(1 + i, 1);
		glEnableVertexAttribArray(1 + i);
	}

	// color
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)sizeof(glm::mat4));
}

Pass::~Pass()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

Renderer::Renderer(Window& window)
	: m_window(window)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_passes = {
		std::make_unique<Pass>(Shader(shaders::basic::vertex, shaders::basic::fragment, "Basic"))
	};
		
	log().debug("Renderer", "Initialized (OpenGL)");
}

void Renderer::updateCamera(const glm::vec2& pos, const PassType& type)
{
	m_camera.move(pos);
	updateCamera(type);
}

void Renderer::updateCamera(const PassType& type) const
{
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_window.width()), 0.0f, static_cast<float>(m_window.height()));
	glm::mat4 view = m_camera.view();
	Shader& shader = (*m_passes[static_cast<int>(type)]).m_shader;
	shader.setMat4("proj", proj);
	shader.setMat4("view", view);
}

void Renderer::renderQuad(const Quad& quad, const PassType& type)
{
	Pass& pass = *m_passes[static_cast<int>(type)];
	if (pass.m_queue.size() >= MAX_INSTANCES) flushPass(type);

}

void Renderer::flushPass(const PassType& type)
{
	Pass& pass = *m_passes[static_cast<int>(type)];
	if (pass.m_queue.empty()) return;

	glBindVertexArray(pass.m_vao);
	pass.m_shader.use();

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices, pass.m_queue.size());
}

void Renderer::begin() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::flush()
{
	for (int i = 0; i < m_passes.size(); i++) flushPass(static_cast<PassType>(i));
}
