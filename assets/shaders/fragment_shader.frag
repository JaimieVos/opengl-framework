#version 330 core

in vec3 v_Normal;
in vec2 v_TexCoords;

out vec4 FragColor;

uniform float u_Alpha;

uniform sampler2D diffuse0;
uniform sampler2D diffuse1;

void main()
{
	FragColor = mix(texture(diffuse0, v_TexCoords), texture(diffuse1, v_TexCoords), 0.2) * vec4(1.0, 1.0, 1.0, u_Alpha);
}