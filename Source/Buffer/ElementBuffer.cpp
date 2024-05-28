#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer(std::vector<uint32_t> *Indices)
{
    glGenBuffers(1, &Id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices->size() * sizeof(uint32_t), Indices->data(), GL_STATIC_DRAW);
}

void ElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void ElementBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::Delete()
{
    glDeleteBuffers(1, &Id);
}