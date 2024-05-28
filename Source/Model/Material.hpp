#ifndef CFD_MATERIAL_HPP
#define CFD_MATERIAL_HPP

#include "Texture.hpp"
#include <vector>

class Material {
private:
    uint8_t bIsLoaded;
    Texture Diffuse;
    // Texture Normal;
    // Texture Specular;
    // Texture Transparent;

    // int8_t bDiffuse;
public:
    Material() : bIsLoaded(false), Diffuse() {}
    void BindAll(Shader *OShader);

    void SetTexture(Texture OTexture) {Diffuse = OTexture;}
};

#endif