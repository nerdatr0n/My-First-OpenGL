#version 450 core
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 colour;

uniform sampler2D tex0;
uniform float	ambientStr		= 0.5f;
uniform vec3	ambientColour	= vec3(1.0f, 1.0f, 1.0f);
uniform vec3	lightColour		= vec3(1.0f, 1.0f, 1.0f);
uniform vec3	lightPos		= vec3(-2.0f, 6.0f, 3.0f);

void main()
{
	// Ambient
	vec3 ambient = ambientStr * ambientColour;

	// Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);

	// Diffuse Colouring
	float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStr * lightColour;

	colour vec4(ambient + diffuse, 1.0f) * (texture(tex0, fragTexCoord));
}