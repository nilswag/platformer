#include <glad/glad.h>

#include "util/log.h"
#include "renderer.h"
#include "shader.h"

#include "shaders/quad.glsl.hpp"

Renderer::Renderer()
{
	m_shaders[(size_t)ShaderType::BASIC] = std::make_unique<Shader>(
		shaders::quad::vertex, shaders::quad::fragment, "Quad"
	);

	log().debug("Renderer", "Initialized (OpenGL)");
}

void Renderer::renderQuad(float x, float y, float width, float height, Color color)
{

}