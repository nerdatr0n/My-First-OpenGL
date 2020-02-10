#version 450 core

void main(void)
{
	const vec3 vertices[] = vec3[](vec3( 0.0f, 0.5f, 0.0f),
									vec3( 0.5f, 0.0f, 0.0f),
									vec3( -0.5f, 0.0f, 0.0f));

	gl_Position = vec4(vertices[gl_VertexID], 1.0f);
}
