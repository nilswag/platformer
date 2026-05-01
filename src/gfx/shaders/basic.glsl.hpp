#pragma once

namespace shaders::basic
{
	inline constexpr const char* vertex = R"(
#version 460 core
layout(location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 proj;

void main()
{
	gl_Position = model * vec4(pos, 1.0);
}
	)";

	inline constexpr const char* fragment = R"(
#version 460 core

uniform vec4 color;

out vec4 FragColor;
		
void main()
{
	FragColor = color;
}
	)";
}