#include "StaticMesh.hpp"

StaticMesh::StaticMesh(std::vector<Vertex> *Vertices, std::vector<uint32_t> *Indices, Material *OMaterial)
{
    StaticMesh::Vertices = *Vertices;
    StaticMesh::Indices = *Indices;
    StaticMesh::OMaterial = *OMaterial;

    OVertexArray.Bind();
    
    VertexBuffer OVertexBuffer(Vertices);
    ElementBuffer OElementBuffer(Indices);

    OVertexArray.LinkAttrib(&OVertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    OVertexArray.LinkAttrib(&OVertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    OVertexArray.LinkAttrib(&OVertexBuffer, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

    OVertexArray.Unbind();
}

void StaticMesh::Link()
{
    OVertexArray.Bind();

    VertexBuffer OVertexBuffer(&Vertices);
    ElementBuffer OElementBuffer(&Indices);

    OVertexArray.LinkAttrib(&OVertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    OVertexArray.LinkAttrib(&OVertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    OVertexArray.LinkAttrib(&OVertexBuffer, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

    OVertexArray.Unbind();
}

void StaticMesh::Draw()
{
    OVertexArray.Bind();

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	OVertexArray.Unbind();
}
