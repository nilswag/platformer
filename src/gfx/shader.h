#pragma once
#include <string>
#include <string_view>
#include <map>
#include <glad/glad.h>

#include "../util/log.h"

class Shader
{
public:
	Shader(std::string_view vertexSrc, std::string_view fragmentSrc, std::string_view tag);
	~Shader();

	void use() const;

	inline unsigned int id() const { return m_id; }
	inline void setFloat(std::string& name, float value) { if (!hasUniform(name)) return; glUniform1f(m_uniforms[name], value); }
	inline void setInt(std::string& name, int value) {     if (!hasUniform(name)) return; glUniform1i(m_uniforms[name], value); }
	inline void setBool(std::string& name, bool value) {   if (!hasUniform(name)) return; glUniform1ui(m_uniforms[name], value); }

private:
	bool compileShader(int& id, std::string_view shaderSrc, unsigned int type) const;

	inline bool hasUniform(std::string& name)
	{
		if (m_uniforms.contains(name)) return true;
		log().err(m_tag, "Uniform not found ({})", name);
		return false;
	}

	unsigned int m_id;
	std::string m_tag;

	std::map<std::string, int> m_uniforms;
};