#pragma once

class Shader
{
public:
	Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag);
	~Shader();

	Shader(const Shader&) = delete;
	void operator=(const Shader&) = delete;

	unsigned int id() const { return m_id; }

private:
	bool compileShader(int& id, const char* shaderSrc, unsigned int type);

	unsigned int m_id;
	const char* m_tag;
};