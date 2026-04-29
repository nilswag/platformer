#pragma once
#include <string>
#include <map>

class Shader
{
public:
	Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag);
	~Shader();

	void use() const;
	unsigned int id() const { return m_id; }

private:
	bool compileShader(int& id, const char* shaderSrc, unsigned int type) const;

	unsigned int m_id;
	std::string m_tag;

	std::map<std::string, int> m_uniforms;
};