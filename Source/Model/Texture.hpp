#ifndef CFD_TEXTURE_H
#define CFD_TEXTURE_H

#include <GL/glew.h>
#include "bmp.h"

#include "Shader.hpp"

class Texture {
public:
	uint32_t Id;
	const char* Type;
	uint32_t Unit;

	Texture(const char *Image, const char *TexType, uint32_t Slot);

	void TexUnit(Shader *OShader, const char *Uniform, uint32_t Unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif