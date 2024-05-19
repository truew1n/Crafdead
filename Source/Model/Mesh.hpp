#ifndef DTD_MESH_H
#define DTD_MESH_H

#include <string>

#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

class Mesh {
public:
	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;
	std::vector<Texture> Textures;
	
	VertexArray OVertexArray;

	Mesh(std::vector<Vertex> *Vertices, std::vector<uint32_t> *Indices, std::vector<Texture> *Textures);

	void Draw(Shader *OShader, Camera *OCamera);
};

#endif