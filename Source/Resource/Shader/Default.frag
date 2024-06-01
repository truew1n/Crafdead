#version 400 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform sampler2D Diffuse;
uniform sampler2D Transparent;
uniform float bTransparent;

void main()
{
    vec4 DiffuseColor = texture(Diffuse, UV);
    float Alpha = texture(Transparent, UV).r;

    vec4 FinalColor = vec4(1.0);
    if(bTransparent == 1.0f) {
        if(Alpha != 1.0) discard;
        else FinalColor = mix(DiffuseColor, vec4(DiffuseColor.rgb, Alpha), 1.0 - Alpha);
    } else {
        FinalColor = DiffuseColor;
    }

    FragColor = FinalColor;
}
