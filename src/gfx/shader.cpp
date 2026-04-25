#include <vector>
#include <glad/glad.h>
#include "shader.h"
#include "util/log.h"

bool Shader::compileShader(int& id, const char* shaderSrc, unsigned int type)
{
	const char* prefix = "INVALID";
	switch (type)
	{
	case GL_VERTEX_SHADER:
		prefix = "VERTEX";
		break;
	case GL_FRAGMENT_SHADER:
		prefix = "FRAGMENT";
		break;
	}

	logger::trace("[Shader:{}][{}] Compile", m_tag, prefix);
	id = glCreateShader(type);
	glShaderSource(id, 1, &shaderSrc, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);

		glGetShaderInfoLog(id, length, nullptr, log.data());
		logger::error("[Shader:{}][{}] Compile failed, reason:\n{}", m_tag, prefix, log.data());
		return false;
	}

	logger::trace("[Shader:{}][{}] Compile ok (ID={})", m_tag, prefix, id);

	return true;
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag)
{
	m_tag = tag;
	m_id = glCreateProgram();

	int vertexShader, fragmentShader;
	if (!compileShader(vertexShader, vertexSrc, GL_VERTEX_SHADER))
		logger::warning("[Shader:{}] No vertex shader", tag);
	if (!compileShader(fragmentShader, fragmentSrc, GL_FRAGMENT_SHADER))
		logger::warning("[Shader:{}] No fragment shader", tag);

	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	int success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);

		glGetProgramInfoLog(m_id, length, nullptr, log.data());
		logger::error("[Shader:{}] Linking failed, reason:\n{}", m_tag, log.data());
		return;
	}

	logger::debug("[Shader:{}] Linked ok (ID={})", tag, m_id);
}

Shader::~Shader()
{

}