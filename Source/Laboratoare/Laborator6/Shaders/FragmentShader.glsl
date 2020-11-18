#version 330

// TODO: get values from fragment shader
in vec3 normal;
in vec2 uw;
in vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(color, 1.0); // switch to normal for task 5
}