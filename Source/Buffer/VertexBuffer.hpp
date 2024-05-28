#ifndef CFD_VERTEX_BUFFER_HPP
#define CFD_VERTEX_BUFFER_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

typedef struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	// glm::vec3 Color; For now useless
	glm::vec2 UV;
} Vertex;

class VertexBuffer {
public:
    uint32_t Id;

    VertexBuffer(std::vector<Vertex> *Vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif