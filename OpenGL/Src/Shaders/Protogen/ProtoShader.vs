#version 330 core
layout (location = 0) in vec3 Base;
layout (location = 1) in vec3 Thoothy;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float thoothy_w;

void main()
{
	float neutral_w = 1.0 - thoothy_w;
	clamp (neutral_w, 0.0, 1.0);

	float sum_w = thoothy_w + neutral_w;
	float thoothy_f = thoothy_w / sum_w;
	float neutral_f = neutral_w / sum_w;

	vec3 pos = thoothy_f * Thoothy + neutral_f  * Base;

	 gl_Position = projection * view * model * vec4(pos, 1.0);
}