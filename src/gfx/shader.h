#pragma once
#include <string>

class Shader
{
public:
	Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag);
	~Shader();

	Shader(const Shader&) = delete;
	void operator=(const Shader&) = delete;

	void use() const;
	unsigned int id() const { return m_id; }

private:
	bool compileShader(int& id, const char* shaderSrc, unsigned int type) const;

	unsigned int m_id;
	std::string m_tag;
};