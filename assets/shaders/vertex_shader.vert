#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

out vec3 v_Normal;
out vec2 v_TexCoords;

void main() 
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
	v_Normal = a_Normal;
	v_TexCoords = a_TexCoords;
}