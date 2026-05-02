#pragma once

namespace shaders::basic
{
	inline constexpr const char* vertex = R"(
#version 460 core
layout (location = 0) in vec3 pos;

layout (location = 1) in vec4 col0;
layout (location = 2) in vec4 col1;
layout (location = 3) in vec4 col2;
layout (location = 4) in vec4 col3;

layout (location = 5) out vec4 color;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	mat4 model = mat4(col0, col1, col2, col3);
	gl_Position = proj * view * model * vec4(pos, 1.0);
}
	)";

	inline constexpr const char* fragment = R"(
#version 460 core
layout (location = 5) in vec4 color;

out vec4 FragColor;
		
void main()
{
	FragColor = color;
}
	)";
}