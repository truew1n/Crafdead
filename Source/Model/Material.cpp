#include "Material.hpp"


void Material::BindAll(Shader *OShader)
{
    if(bDiffuse) {
        Diffuse.TextureUnit(OShader, "Diffuse", 0);
        Diffuse.Bind();
    }

    // Normal.TextureUnit(OShader, "Normal0", 0);
    // Normal.Bind();

    // Specular.TextureUnit(OShader, "Specular0", 0);
    // Specular.Bind();

    uint32_t UnitLocation = glGetUniformLocation(OShader->GetId(), "bTransparent");
    if(bTransparent) {
        Transparent.TextureUnit(OShader, "Transparent", 1);
	    glUniform1f(UnitLocation, 1.0f);
        Transparent.Bind();
    } else {
        glUniform1f(UnitLocation, 0.0f);
    }
}

void Material::UnbindAll()
{
    if(bDiffuse) {
        Diffuse.Unbind();
    }

    // Normal.TextureUnit(OShader, "Normal0", 0);
    // Normal.Bind();

    // Specular.TextureUnit(OShader, "Specular0", 0);
    // Specular.Bind();

    if(bTransparent) {
        Transparent.Unbind();
    }
}

void Material::SetTexture(Texture OTexture, TextureType Type)
{
    switch(Type) {
        case TextureType::DIFFUSE: {
            Diffuse = OTexture;
            bDiffuse = true;
            break;
        }
        case TextureType::TRANSPARENT: {
            Transparent = OTexture;
            bTransparent = true;
            break;
        }
    }
}

