#pragma once

namespace shaders::basic
{
	inline constexpr const char* vertex = R"(
#version 460 core
layout (location = 0) in vec3 pos;

layout (location = 5) in vec4 aColor;
out vec4 color;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * vec4(pos, 1.0);
	color = aColor;
}
	)";

	inline constexpr const char* fragment = R"(
#version 460 core
in vec4 color;
out vec4 FragColor;
		
void main()
{
	FragColor = color;
}
	)";
}