#version 330 core

in vec3 v_Normal;
in vec2 v_TexCoords;
in vec3 v_FragPos;

out vec4 FragColor;

uniform sampler2D diffuse0;

void main()
{
	vec3 lightPos = vec3(1.0, 0.5, 1.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	// Ambient lighting
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse lighting
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * 10;
	
	FragColor = vec4(ambient * diffuse, 1) * texture(diffuse0, v_TexCoords);
}