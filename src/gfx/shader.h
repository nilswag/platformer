#pragma once
#include <string>
#include <string_view>
#include <map>

class Shader
{
public:
	Shader(std::string_view vertexSrc, std::string_view fragmentSrc, std::string_view tag);
	~Shader();

	void use() const;
	unsigned int id() const { return m_id; }

private:
	bool compileShader(int& id, std::string_view shaderSrc, unsigned int type) const;

	unsigned int m_id;
	std::string m_tag;

	std::map<std::string, int> m_uniforms;
};