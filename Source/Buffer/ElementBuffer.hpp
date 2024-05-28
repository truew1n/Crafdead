#ifndef CFD_ELEMENT_BUFFER_HPP
#define CFD_ELEMENT_BUFFER_HPP

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