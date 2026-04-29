#pragma once

namespace shaders::basic
{
	inline constexpr const char* vertex = R"(
#version 460 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

layout(location = 0) out vec4 vColor;

void main()
{
	gl_Position = vec4(pos, 1.0);
	vColor = color;
}
	)";

	inline constexpr const char* fragment = R"(
#version 460 core
layout(location = 0) in vec4 color;

out vec4 FragColor;
		
void main()
{
	FragColor = color;
}
	)";
}