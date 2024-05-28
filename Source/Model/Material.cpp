#include "Material.hpp"


void Material::BindAll(Shader *OShader)
{
    Diffuse.TextureUnit(OShader, "Diffuse", 0);
    Diffuse.Bind();

    // Normal.TextureUnit(OShader, "Normal0", 0);
    // Normal.Bind();

    // Specular.TextureUnit(OShader, "Specular0", 0);
    // Specular.Bind();

    // Specular.TextureUnit(OShader, "Transparent0", 0);
    // Specular.Bind();
}

