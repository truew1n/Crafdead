#ifndef CFD_TEXTURE_HPP
#define CFD_TEXTURE_HPP

#include <GL/glew.h>

#include "Shader.hpp"

#include "stb_image.h"

class Texture {
private:
	uint32_t Id;
	const char *Type;
	uint32_t Unit;
public:
	Texture() : Id(0), Type(nullptr), Unit(0) {};
	Texture(const char *Image, const char *TextureType, uint32_t Slot);

	void TextureUnit(Shader *OShader, const char *Uniform, uint32_t Unit);
	void Bind();
	void Unbind();
	void Delete();

	uint32_t GetId() { return Id; }
	const char *GetType() { return Type; }
};

#endif