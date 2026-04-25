#include <vector>
#include <glad/glad.h>
#include "shader.h"
#include "util/log.h"

static bool compileShader(int& id, const char* shaderSrc, unsigned int type)
{
	logger::trace("Compiling shader:\n{}", shaderSrc);
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
		logger::error("Error while compiling shader:\n{}", log.data());
		return false;
	}

	logger::trace("Compiled shader.");

	return true;
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag)
{
	m_id = glCreateProgram();

	int vertexShader, fragmentShader;
	if (!compileShader(vertexShader, vertexSrc, GL_VERTEX_SHADER))
		logger::warning("Uncompiled vertex shader.");
	if (!compileShader(fragmentShader, fragmentSrc, GL_FRAGMENT_SHADER))
		logger::warning("Uncompiled fragment shader.");

	logger::debug("Initialized shader ({}).", tag);
}

Shader::~Shader()
{

}