#ifndef DTD_TEXTURE_H
#define DTD_TEXTURE_H

#include <GL/glew.h>
#include "bmp.h"

#include "Shader.hpp"

class Texture {
public:
	uint32_t Id;
	const char* Type;
	uint32_t Unit;

	Texture(const char *Image, const char *TexType, uint32_t Slot, uint32_t Format, uint32_t PixelType);

	void TexUnit(Shader *TargetShader, const char *Uniform, uint32_t Unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif