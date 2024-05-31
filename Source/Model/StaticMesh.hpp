#ifndef CFD_STATIC_MESH_HPP
#define CFD_STATIC_MESH_HPP

#include <string>

#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Camera.hpp"
#include "Material.hpp"

#include <iostream>

class StaticMesh {
private:
	uint8_t bIsLoaded;
	VertexArray OVertexArray;

	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;

	Material OMaterial;
public:
	StaticMesh() : OVertexArray(), Vertices(), Indices(), OMaterial() {}
	StaticMesh(std::vector<Vertex> *Vertices, std::vector<uint32_t> *Indices, Material *OMaterial);
	void Link();

	void Draw();

	void AddVertex(Vertex OVertex) { Vertices.push_back(OVertex); }
	int64_t GetVerticesSize() { return Vertices.size(); }
	void AddIndex(uint32_t Index) { Indices.push_back(Index); }
	void SetMaterial(Material *OMaterial) { this->OMaterial = *OMaterial; }
	Material *GetMaterial() { return &this->OMaterial; }
};

#endif