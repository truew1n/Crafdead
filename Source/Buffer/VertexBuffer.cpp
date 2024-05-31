#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex> *Vertices)
{
    glGenBuffers(1, &Id);
	glBindBuffer(GL_ARRAY_BUFFER, Id);
	glBufferData(GL_ARRAY_BUFFER, Vertices->size() * sizeof(Vertex), Vertices->data(), GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete()
{
    glDeleteBuffers(1, &Id);
}