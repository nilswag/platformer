#include <glad/glad.h>
#include "renderer.h"

Renderer& Renderer::getInstance()
{
	static Renderer renderer;
	return renderer;
}

void Renderer::renderQuad(Quad& quad)
{

}

void Renderer::renderQuad(float x, float y, float width, float height, Color color = WHITE)
{

}