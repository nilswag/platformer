#pragma once

namespace shaders::basic
{
	inline constexpr const char* vertex = R"(
#version 460 core
layout (location = 0) in vec3 pos;

void main()
{
	gl_Position = vec4(pos, 1.0);
}
	)";

	inline constexpr const char* fragment = R"(
#version 460 core
out vec4 FragColor;
		
void main()
{
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
	)";
}