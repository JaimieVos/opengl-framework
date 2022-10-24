#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 v_TexCoords;

void main()
{
    v_TexCoords = vec3(a_Position.x, -a_Position.y, a_Position.z);
    gl_Position = (u_Projection * u_View * vec4(a_Position, 1.0)).xyww;
}  