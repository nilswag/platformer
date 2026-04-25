#pragma once

class Shader
{
public:
	Shader(const char* vertexSrc, const char* fragmentSrc, const char* tag = "Unspecified");
	~Shader();

	Shader(const Shader&) = delete;
	void operator=(const Shader&) = delete;

	unsigned int id() const { return m_id; }

private:
	unsigned int m_id;

};