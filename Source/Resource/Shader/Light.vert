#version 330 core

layout (location = 0) in vec3 LPosition;

uniform mat4 Model;
uniform mat4 CameraMatrix;

void main()
{
	gl_Position = CameraMatrix * Model * vec4(LPosition, 1.0f);
}