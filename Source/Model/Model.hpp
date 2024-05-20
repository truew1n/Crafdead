#ifndef CFD_MODEL_H
#define CFD_MODEL_H

#include "Mesh.hpp"

class Model {
private:
    
public:
    Model(const char *Filepath);

    void Draw(Shader *OShader, Camera *OCamera);
};

#endif