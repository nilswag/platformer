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
	
}


Pass::~Pass()
{

}


Renderer::Renderer(Window& window)
	: m_window(window)
{
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
