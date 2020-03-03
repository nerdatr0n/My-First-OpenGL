#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D tex;


void main()
{
	// vec3 colorTemp = fragColor * abs(sin(currentTime));
	color = texture(tex, fragTexCoord); // vec4(colorTemp, 1.0f);
}

