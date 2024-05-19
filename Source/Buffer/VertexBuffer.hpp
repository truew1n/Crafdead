#ifndef DTD_VERTEX_BUFFER_H
#define DTD_VERTEX_BUFFER_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

typedef struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
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