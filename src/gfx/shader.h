#pragma once
#include <string>
#include <string_view>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../util/log.h"

class Shader
{
public:
	Shader(std::string_view vertexSrc, std::string_view fragmentSrc, std::string_view tag);
	~Shader();

	void use() const;

	inline unsigned int id() const { return m_id; }
	inline void setFloat(const std::string& name, float value) { if (!hasUniform(name)) return; glUniform1f(m_uniforms[name], value); }
	inline void setInt(const std::string& name, int value) { if (!hasUniform(name)) return; glUniform1i(m_uniforms[name], value); }
	inline void setBool(const std::string& name, bool value) { if (!hasUniform(name)) return; glUniform1i(m_uniforms[name], value); }
	inline void setVec2(const std::string& name, const glm::vec2& value) { if (!hasUniform(name)) return; glUniform2fv(m_uniforms[name], 1, glm::value_ptr(value)); }
	inline void setVec3(const std::string& name, const glm::vec3& value) { if (!hasUniform(name)) return; glUniform3fv(m_uniforms[name], 1, glm::value_ptr(value)); }
	inline void setVec4(const std::string& name, const glm::vec4& value) { if (!hasUniform(name)) return; glUniform4fv(m_uniforms[name], 1, glm::value_ptr(value)); }
	inline void setMat2(const std::string& name, const glm::mat2& value) { if (!hasUniform(name)) return; glUniformMatrix2fv(m_uniforms[name], 1, GL_FALSE, glm::value_ptr(value)); }
	inline void setMat3(const std::string& name, const glm::mat3& value) { if (!hasUniform(name)) return; glUniformMatrix3fv(m_uniforms[name], 1, GL_FALSE, glm::value_ptr(value)); }
	inline void setMat4(const std::string& name, const glm::mat4& value) { if (!hasUniform(name)) return; glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, glm::value_ptr(value)); }

private:
	bool compileShader(int& id, std::string_view shaderSrc, unsigned int type) const;

	inline bool hasUniform(const std::string& name)
	{
		if (m_uniforms.contains(name)) return true;
		log().err(m_tag, "Uniform not found: {}", name);
		return false;
	}

	unsigned int m_id;
	std::string m_tag;

	std::map<std::string, int> m_uniforms;
};