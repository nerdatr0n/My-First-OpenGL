#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;



out vec2 fragTexCoord;

uniform mat4 MVP;


void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	fragTexCoord = texCoord;
}
