#pragma once

namespace shaders::basic
{
	inline constexpr const char* vertex = R"(
		#version 460 core
		layout(location = 0) in vec3 pos;

		void main()
		{
			gl_Position = vec4(pos, 1.0f);
		}
	)";

	inline constexpr const char* fragment = R"(
		#version 460 core
		out vec4 color;
		
		void main()
		{
			color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";
}