#include <string>
#include <glad/glad.h>
#include <vector>
#include <spdlog/spdlog.h>

#include "shader.h"

GLuint Shader::compileShader(const std::string& src, GLenum type)
{
	GLuint id = glCreateShader(type);
	const GLchar* srcStr = static_cast<const GLchar*>(src.c_str());
	glShaderSource(id, 1, &srcStr, src.length());
	glCompileShader(id);

	std::string tag = "N/A";
	switch (type)
	{
	case GL_VERTEX_SHADER:
		tag = "Vertex";
		break;
	case GL_FRAGMENT_SHADER:
		tag = "Fragment";
		break;
	}

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::vector<GLchar> log;
		GLint logLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
		log.resize(logLength);

		glGetShaderInfoLog(id, log.size(), nullptr, log.data());
		
		spdlog::error("Unable to compile shader ({}, {}): {}", id, tag, log);
	}

	spdlog::trace("Compiled shader ({}, {})", id, type);
	return id;
}

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& tag)
	: m_tag(tag)
{
	GLuint vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	
	m_id = glCreateProgram();
	glAttachShader(vertexShader, GL_VERTEX_SHADER);
	glAttachShader(fragmentShader, GL_FRAGMENT_SHADER);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::vector<GLchar> log;
		GLint logLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
		log.resize(logLength);

		glGetProgramInfoLog(id, log.size(), nullptr, log.data());

		spdlog::error("Unable to linik shader program ({}): {}", id, log);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}