#pragma once
#include <array>
#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

#include "window.h"
#include "shader.h"
#include "camera.h"
#include "quad.h"

struct Pass
{
	Pass(const Shader& shader);
	~Pass();

	Shader m_shader;
	unsigned int m_vao, m_ibo;
	std::vector<Quad> m_queue;
};

enum class PassType
{
	BASIC = 0,
	N
};

class Renderer
{
public:
	Renderer(Window& window);
	~Renderer() = default;

	Renderer(const Renderer&) = delete;
	void operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	void operator=(Renderer&&) = delete;
	
	void updateCamera(const glm::vec2& pos, const PassType& type);
	void updateCamera(const PassType& type) const;
	void renderQuad(const Quad& quad, const PassType& type);
	void flushPass(const PassType& type);
	void begin() const;
	void flush();

private:
	Window& m_window;
	Camera m_camera;
	unsigned int m_vao;

	std::array<std::unique_ptr<Pass>, static_cast<int>(PassType::N)> m_passes;
};