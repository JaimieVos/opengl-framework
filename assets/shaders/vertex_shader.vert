#version 330 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

out vec3 v_Color;
out vec2 v_TexCoords;

void main() 
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 0.0, 1.0);
	v_Color = a_Color;
	v_TexCoords = a_TexCoords;
}