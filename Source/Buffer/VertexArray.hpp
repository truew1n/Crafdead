#ifndef CFD_VERTEX_ARRAY_HPP
#define CFD_VERTEX_ARRAY_HPP

#include <GL/glew.h>
#include "VertexBuffer.hpp"

class VertexArray {
public:
	uint32_t Id;

	VertexArray();

	void LinkAttrib(VertexBuffer *OVertexBuffer, uint32_t Layout, uint32_t ComponentCount, uint32_t Type, ptrdiff_t Stride, void *Offset);
	void Bind();
	void Unbind();
	void Delete();
};
    
#endif