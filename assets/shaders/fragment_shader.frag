#version 330 core

in vec3 v_Color;
in vec2 v_TexCoords;

out vec4 FragColor;

uniform float u_Alpha;

uniform sampler2D diffuse0;
uniform sampler2D diffuse1;

void main()
{
	FragColor = mix(texture(diffuse0, v_TexCoords), texture(diffuse1, v_TexCoords), 0.2) * vec4(v_Color, u_Alpha);
}