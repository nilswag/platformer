#include <string>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "../math/mat.h"
#include "shader.h"

GLuint Shader::compileShader(const std::string& src, GLenum type)
{
	GLuint id = glCreateShader(type);
	const GLchar* srcStr = static_cast<const GLchar*>(src.c_str());
	glShaderSource(id, 1, &srcStr, nullptr);
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
		std::string log;
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		log.resize(length);

		glGetShaderInfoLog(id, log.size(), nullptr, log.data());
		
		spdlog::error("Unable to compile shader ({}:{}):\n{}", m_tag, tag, log);
		return id;
	}

	spdlog::trace("Compiled shader ({}:{})", m_tag, tag);
	return id;
}

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& tag)
	: m_id(0), m_tag(tag)
{
	if (vertexSrc == "")
	{
		spdlog::warn("Vertex shader source empty ({})", m_tag);
		return;
	}

	if (fragmentSrc == "")
	{
		spdlog::warn("Fragment shader source empty ({})", m_tag);
		return;
	}

	GLuint vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	
	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		std::string log;
		log.resize(length);

		glGetProgramInfoLog(m_id, log.size(), nullptr, log.data());

		spdlog::error("Unable to link shader program ({}):\n{}", m_id, log);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::setVec2(const std::string& name, const Vec2& value) const
{
	if (!hasUniform(name)) return;
	glUniform2iv(m_uniforms.at(name), 1, value.data);
}

void Shader::setVec3(const std::string& name, const Vec3& value) const
{
	if (!hasUniform(name)) return;
	glUniform3iv(m_uniforms.at(name), 1, value.data);
}

void Shader::setVec4(const std::string& name, const Vec4& value) const
{
	if (!hasUniform(name)) return;
	glUniform4iv(m_uniforms.at(name), 1, value.data);
}

void Shader::setVec2f(const std::string& name, const Vec2f& value) const
{
	if (!hasUniform(name)) return;
	glUniform2fv(m_uniforms.at(name), 1, value.data);
}

void Shader::setVec3f(const std::string& name, const Vec3f& value) const
{
	if (!hasUniform(name)) return;
	glUniform3fv(m_uniforms.at(name), 1, value.data);
}

void Shader::setVec4f(const std::string& name, const Vec4f& value) const
{
	if (!hasUniform(name)) return;
	glUniform4fv(m_uniforms.at(name), 1, value.data);
}

void Shader::setMat2f(const std::string& name, const Mat2f& value) const
{
	if (!hasUniform(name)) return;
	glUniformMatrix2fv(m_uniforms.at(name), 1, GL_FALSE, value[0].data);
}

void Shader::setMat3f(const std::string& name, const Mat3f& value) const
{
	if (!hasUniform(name)) return;
	glUniformMatrix3fv(m_uniforms.at(name), 1, GL_FALSE, value[0].data);
}

void Shader::setMat4f(const std::string& name, const Mat4f& value) const
{
	if (!hasUniform(name)) return;
	glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, value[0].data);
}