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
	gl_Position = vec4(pos, 1.0f);
	vColor = color;
}
	)";

	inline constexpr const char* fragment = R"(
#version 460 core
layout(location = 0) in vec4 color;

out vec4 FragColor;
		
uniform vec3 test;

void main()
{
	FragColor = vec4(test, 1.0f);
}
	)";
}