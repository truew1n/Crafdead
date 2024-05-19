#include "Texture.hpp"

Texture::Texture(const char *Image, const char *TexType, uint32_t Slot, uint32_t Format, uint32_t PixelType)
{
    Type = TexType;

    bmp_t TextureImage = open_bmp(Image);

	glGenTextures(1, &Id);
	
	glActiveTexture(GL_TEXTURE0 + Slot);
	Unit = Slot;
	glBindTexture(GL_TEXTURE_2D, Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage.width, TextureImage.height, 0, Format, PixelType, TextureImage.memory);
	glGenerateMipmap(GL_TEXTURE_2D);

	free(TextureImage.memory);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TexUnit(Shader *TargetShader, const char *Uniform, uint32_t Unit)
{
	uint32_t TexUnitLocation = glGetUniformLocation(TargetShader->Id, Uniform);
	
	TargetShader->Activate();
	
	glUniform1i(TexUnitLocation, Unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + Unit);
	glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &Id);
}