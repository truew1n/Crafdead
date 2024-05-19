#version 330 core
#extension GL_ARB_separate_shader_objects : enable

out vec4 FragColor;


in vec2 TexCord;
uniform sampler2D Tex0;


void main()
{
   FragColor = texture(Tex0, TexCord);
}