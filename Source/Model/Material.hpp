#ifndef CFD_MATERIAL_HPP
#define CFD_MATERIAL_HPP

#include "Texture.hpp"
#include <vector>

enum class TextureType : uint8_t {
    DIFFUSE,
    TRANSPARENT
};

class Material {
private:
    uint8_t bIsLoaded;
    Texture Diffuse;
    // Texture Normal;
    // Texture Specular;
    Texture Transparent;

    bool bDiffuse;
    bool bTransparent;
public:
    Material() : bIsLoaded(false), Diffuse(), Transparent(), bDiffuse(false), bTransparent(false)  {}
    void BindAll(Shader *OShader);
    void UnbindAll();

    void SetTexture(Texture OTexture, TextureType Type);
    bool IsTransparent() const { return bTransparent; }
};

#endif