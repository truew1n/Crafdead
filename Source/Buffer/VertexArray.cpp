#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &Id);
}

void VertexArray::LinkAttrib(VertexBuffer *OVertexBuffer, uint32_t Layout, uint32_t ComponentCount, uint32_t Type, ptrdiff_t Stride, void *Offset)
{
    OVertexBuffer->Bind();
	glVertexAttribPointer(Layout, ComponentCount, Type, GL_FALSE, Stride, Offset);
	glEnableVertexAttribArray(Layout);
	OVertexBuffer->Unbind();
}

void VertexArray::Bind()
{
    glBindVertexArray(Id);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::Delete()
{
    glDeleteVertexArrays(1, &Id);
}