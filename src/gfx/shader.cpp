#include <string>
#include <glad/glad.h>

#include "util/log.h"
#include "shader.h"

bool Shader::compileShader(int& id, const char* shaderSrc, unsigned int type) const
{
	std::string typeStr;
	switch (type)
	{
	case GL_VERTEX_SHADER:
		typeStr = "Vertex";
		break;
	case GL_FRAGMENT_SHADER:
		typeStr = "Fragment";
		break;
	default:
		typeStr = "???";
		break;
	}

	log().trace(m_tag, "Compile ({})", typeStr);
	id = glCreateShader(type);
	glShaderSource(id, 1, &shaderSrc, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::string str;
		str.resize(length);

		glGetShaderInfoLog(id, length, nullptr, str.data());
		log().err(m_tag, "Compile error ({}), reason:\n{}", typeStr, str);
		return false;
	}

	log().trace(m_tag, "Compile ok ({}, ID={})", typeStr, id);

	return true;
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag)
{
	m_tag = std::format("Shader:{}", tag);
	m_id = glCreateProgram();

	int vertexShader, fragmentShader;
	if (!compileShader(vertexShader, vertexSrc, GL_VERTEX_SHADER))
		log().warn(m_tag, "No vertex shader");
	if (!compileShader(fragmentShader, fragmentSrc, GL_FRAGMENT_SHADER))
		log().warn(m_tag, "No fragment shader");

	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	int success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		std::string str;
		str.resize(length);

		glGetProgramInfoLog(m_id, length, nullptr, str.data());
		log().err(m_tag, "Linking failed, reason:\n{}", str);
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int count = 0;
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &count);
	for (int i = 0; i < count; i++)
	{
		std::string name;
		glGetActiveUniform(m_id, i, name.size(), );
	}

	log().debug(m_tag, "Linking ok (ID={})", m_id);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::use() const
{
	glUseProgram(m_id);
}