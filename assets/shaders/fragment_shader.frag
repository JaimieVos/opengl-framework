#version 330 core

in vec3 v_Normal;
in vec2 v_TexCoords;

out vec4 FragColor;

uniform float u_Alpha;
uniform bool u_Smiley;

uniform sampler2D diffuse0;
uniform sampler2D diffuse1;

void main()
{
	if (u_Smiley)
		FragColor = mix(texture(diffuse0, v_TexCoords), texture(diffuse1, v_TexCoords) * u_Alpha, 0.2);
	else
		FragColor =  texture(diffuse0, v_TexCoords);
}