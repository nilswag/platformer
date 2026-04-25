#include <vector>
#include <format>
#include <glad/glad.h>
#include "shader.h"
#include "util/log.h"

bool Shader::compileShader(int& id, const char* shaderSrc, unsigned int type)
{
	log().trace(std::format("Shader:{}", m_tag), "Compile");
	id = glCreateShader(type);
	glShaderSource(id, 1, &shaderSrc, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> infoLog(length);

		glGetShaderInfoLog(id, length, nullptr, infoLog.data());
		log().err(std::format("Shader:{}", m_tag), "Compile error, reason:\n{}", infoLog.data());
		return false;
	}

	log().trace(std::format("Shader:{}", m_tag), "Compile ok(ID = {})", id);

	return true;
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag)
{
	m_tag = tag;
	m_id = glCreateProgram();

	int vertexShader, fragmentShader;
	if (!compileShader(vertexShader, vertexSrc, GL_VERTEX_SHADER))
		log().warn(std::format("Shader:{}", m_tag), "No vertex shader");
	if (!compileShader(fragmentShader, fragmentSrc, GL_FRAGMENT_SHADER))
		log().warn(std::format("Shader:{}", m_tag), "No fragment shader");

	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	int success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> infoLog(length);

		glGetProgramInfoLog(m_id, length, nullptr, infoLog.data());
		log().err(std::format("Shader:{}", m_tag), "Linking failed, reason:\n{}", infoLog.data());
		return;
	}

	log().debug(std::format("Shader:{}", m_tag), "Linking ok (ID={})", m_id);
}

Shader::~Shader()
{

}