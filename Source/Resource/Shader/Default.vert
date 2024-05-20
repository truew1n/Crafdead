#version 330 core

layout (location = 0) in vec3 LPosition;
layout (location = 1) in vec3 LNormal;
layout (location = 2) in vec3 LColor;
layout (location = 3) in vec2 LUV;

out vec3 Position;
out vec3 Normal;
out vec3 Color;
out vec2 UV;

uniform mat4 Model;
uniform mat4 CameraMatrix;


void main()
{
	Position = vec3(Model * vec4(LPosition, 1.0f));
	Normal = LNormal;
	Color = LColor;
	UV = LUV;
	
	gl_Position = CameraMatrix * vec4(Position, 1.0);
}