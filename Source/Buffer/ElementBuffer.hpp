#ifndef DTD_ELEMENT_BUFFER_H
#define DTD_ELEMENT_BUFFER_H

#include <GL/glew.h>
#include <vector>

class ElementBuffer {
public:
    uint32_t Id;

    ElementBuffer(std::vector<uint32_t> *Indices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif