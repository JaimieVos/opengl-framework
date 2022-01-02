#version 330 core

in vec3 v_Color;
in vec2 v_TexCoords;

out vec4 FragColor;

uniform float u_Alpha;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
	FragColor = mix(texture(u_Texture1, v_TexCoords), texture(u_Texture2, v_TexCoords), 0.2) * vec4(v_Color, u_Alpha);
}