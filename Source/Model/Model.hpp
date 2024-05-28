#ifndef CFD_MODEL_HPP
#define CFD_MODEL_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "StaticMesh.hpp"

class Model {
private:
    uint8_t bIsLoaded;
    std::vector<StaticMesh> StaticMeshes;
    
    void Split(std::string *String, std::vector<std::string> *Tokens, char Delimiter);
    void ParseMTL(const char *Filepath, std::unordered_map<std::string, std::string> *MTL);
public:
    Model() : bIsLoaded(false), StaticMeshes() {}
    void LoadOBJ(const char *Filepath);

    void Draw(Shader *OShader, Camera *OCamera);
};

#endif

/* Notes
Model will hold:
    Meshes
StaticMesh will hold:
    Vertices
    Indices
    Materials
Material will hold:
    Textures
    Uniform Data shared across all textures
Texture will hold:
    Handling of Loading itself
    And passing itself to shader
*/
/* .obj File Format Structure:
# This is a comment                             | Comment just skip until new line
mtllib model.mtl                                | There are informations about textures and their locations more about it later
o object_name                                   | Gives name of the object
v -0.1 0.0f 0.0                                 | Vertex Positions
...                                             | ...
v -0.1 0.0 0.0                                  | ...
vn 0.7 0.5 0.3                                  | Vertex Normals
...                                             | ...
vn 0.2 0.5 0.1                                  | ...
vt -0.3 0.5                                     | Vertex UV
...                                             | ...
vt 0.1 -0.4                                     | ...
usemtl texture_01                               | This Texture can be a group of Textures like Diffuse + Transparency + Normal + Specular...
f 135/135/99 138/138/101 137/137/100            | Faces in format: v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
...                                             | ...
f 634/634/437 635/635/438 636/636/437           | ...

Single .obj file can have multiple objects in format on top
*/

/* .mtl File Format Structure
newmtl texture_01                               | This is texture_01 from before
Ns 40.551991                                    | Specular Exponent
Ka 1.000000 1.000000 1.000000                   | Ambient Reflectivity
Ks 0.050000 0.050000 0.050000                   | Specular Reflectivity
Ke 0.000000 0.000000 0.000000                   | Emissive Color
Ni 1.450000                                     | Optical Density / Index of Refraction
illum 2                                         | Illumination Model
d
map_Kd texture_01_Color.png                     | Diffuse - Texture
map_d texture_01_Transparency.png               | Transparency - Texture
map_Ks texture_Specular.png                     | Specular - Texture
map_Bump texture_01_Normal.png                  | Normal - Texture
*/