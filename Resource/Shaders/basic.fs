#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D tex;
uniform sampler2D tex1;

void main()
{
	// vec3 colorTemp = fragColor * abs(sin(currentTime));
	color = mix(texture(tex, fragTexCoord), texture(tex1, fragTexCoord), abs(sin(currentTime * 0.5))); // vec4(colorTemp, 1.0f);
}

