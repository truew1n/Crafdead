#version 330 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform sampler2D Diffuse;

void main()
{
	FragColor = texture(Diffuse, UV);
	// FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}