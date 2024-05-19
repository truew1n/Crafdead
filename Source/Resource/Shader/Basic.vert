#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 Tex;

out vec2 TexCord;

uniform mat4 CameraMatrix;

void main()
{
   gl_Position = CameraMatrix * Position;
   TexCord = Tex;
}