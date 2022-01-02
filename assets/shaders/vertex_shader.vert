#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoords;

out vec3 v_Color;
out vec2 v_TexCoords;

void main() 
{
	gl_Position = vec4(a_Position, 0.0, 1.0);
	v_Color = a_Color;
	v_TexCoords = a_TexCoords;
}