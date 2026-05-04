#pragma once
#include <string>
#include <glad/glad.h>
#include <map>
#include <spdlog/spdlog.h>

#include "../math/math.h"

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc, std::string& tag);
	~Shader();

	inline GLuint getId() const { return id; }

	void setVec2(const std::string& name, const Vec2& value) const;
	void setVec4(const std::string& name, const Vec3& value) const;
	void setVec4(const std::string& name, const Vec4& value) const;

	void setVec2f(const std::string& name, const Vec2f& value) const;
	void setVec4f(const std::string& name, const Vec3f& value) const;
	void setVec4f(const std::string& name, const Vec4f& value) const;

	void setMat2(const std::string& name, const Mat2& value) const;
	void setMat3(const std::string& name, const Mat3& value) const;
	void setMat4(const std::string& name, const Mat4& value) const;

	void setMat2f(const std::string& name, const Mat2f& value) const;
	void setMat3f(const std::string& name, const Mat3f& value) const;
	void setMat4f(const std::string& name, const Mat4f& value) const;

private:
	std::map<std::string, GLint> uniforms;
	std::string m_tag;
	GLuint m_id;

	GLint compileShader(const std::string src, GLenum type);

	inline bool hasUniform(const std::string& name) const
	{
		if (uniforms.contains(name)) return true;
		spdlog::error("Uniform does not exist: {}", name);
		return false;
	}
};