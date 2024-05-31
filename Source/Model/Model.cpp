#include "Model.hpp"

void Model::Draw(Shader *OShader, Camera *OCamera)
{
    for (StaticMesh OStaticMesh : StaticMeshes) {
        OShader->Activate();
        OStaticMesh.GetMaterial()->BindAll(OShader);
        
        glUniform3f(glGetUniformLocation(OShader->GetId(), "CameraPosition"), OCamera->Position.x, OCamera->Position.y, OCamera->Position.z);
        OCamera->Matrix(OShader, "CameraMatrix");
        

        if(OStaticMesh.GetMaterial()->IsTransparent()) {
            glDisable(GL_CULL_FACE);
            OStaticMesh.Draw();
            glEnable(GL_CULL_FACE);
        } else {
            OStaticMesh.Draw();
        }

        OStaticMesh.GetMaterial()->UnbindAll();
    }
}

void Model::Split(std::string *String, std::vector<std::string> *Tokens, char Delimiter)
{
    std::stringstream StringStream(*String);
    std::string Token;
    while (std::getline(StringStream, Token, Delimiter)) {
        if (!Token.empty()) {
            Tokens->push_back(Token);
        }
    }
}

void Model::ParseMTL(const char *Filepath, MTLLIB *MTL)
{
    std::ifstream File(Filepath);
    if (!File.is_open()) {
        std::cerr << "Unable to open file: " << Filepath << "!" << std::endl;
        return;
    }

    std::vector<std::string> Tokens;
    std::string Line;
    uint8_t FoundKey = false;
    std::string CurrentKey;
    while (std::getline(File, Line)) {
        Split(&Line, &Tokens, ' ');
        if(Tokens.empty());

        if(Tokens[0] == "newmtl") {
            FoundKey = true;
            CurrentKey = Tokens[1];
        } else if(Tokens.size() == 2) {
            if(FoundKey) {
                (*MTL)[CurrentKey][Tokens[0]] = Tokens[1];
            }
        } else if(Tokens.size() == 4) {
            if(FoundKey) {
                (*MTL)[CurrentKey][Tokens[0]] = Tokens[1] + Tokens[2] + Tokens[3];
            }
        }
        
        Tokens.clear();
    }
}

void Model::LoadOBJ(const char *Filepath)
{
    std::ifstream File(Filepath);
    if (!File.is_open()) {
        std::cerr << "Unable to open file: " << Filepath << "!" << std::endl;
        return;
    }

    std::string StringFilepath(Filepath);
    std::string FileDirectory = StringFilepath.substr(0, StringFilepath.find_last_of('\\') + 1);
    
    StaticMesh OStaticMesh;

    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec2> UVs;

    MTLLIB MTL;
    std::vector<std::string> Tokens;
    std::string Line;

    uint16_t MaterialCount = 0;
    Material OMaterial;

    std::vector<std::pair<std::string, TextureType>> TextureFilepaths;
    while (std::getline(File, Line)) {
        Split(&Line, &Tokens, ' ');
        if(Tokens.empty());

        if(Tokens[0] == "f") {
            std::vector<std::string> FaceTokens;
            for(uint32_t i = 1; i < 4; ++i) {
                Split(&Tokens[i], &FaceTokens, '/');
                uint32_t RealIndex = OStaticMesh.GetVerticesSize();
                
                Vertex OVertex;
                OVertex.Position = Vertices[std::stoi(FaceTokens[0]) - 1];
                OVertex.Normal = Normals[std::stoi(FaceTokens[2]) - 1];
                OVertex.UV = UVs[std::stoi(FaceTokens[1]) - 1];

                OStaticMesh.AddVertex(OVertex);
                
                OStaticMesh.AddIndex(RealIndex);
                FaceTokens.clear();
            }
        } else if(Tokens[0] == "vt") {
            UVs.push_back(glm::vec2(
                std::stof(Tokens[1]),
                std::stof(Tokens[2])
            ));
        } else if(Tokens[0] == "vn") {
            Normals.push_back(glm::vec3(
                std::stof(Tokens[1]),
                std::stof(Tokens[2]),
                std::stof(Tokens[3])
            ));
        } else if(Tokens[0] == "v") {
            Vertices.push_back(glm::vec3(
                std::stof(Tokens[1]),
                std::stof(Tokens[2]),
                std::stof(Tokens[3])
            ));
        } else if(Tokens[0] == "usemtl") {
            if (MaterialCount) {
                for(std::pair<std::string, TextureType> TextureData : TextureFilepaths) {
                    const char *StringType = "Diffuse";
                    switch(TextureData.second) {
                        case TextureType::DIFFUSE: {
                            StringType = "Diffuse";
                            break;
                        }
                        case TextureType::TRANSPARENT: {
                            StringType = "Transparent";
                            break;
                        }
                    }
                    OMaterial.SetTexture(Texture(TextureData.first.c_str(), StringType, (uint32_t) TextureData.second), TextureData.second);
                }
                TextureFilepaths.clear();
                OStaticMesh.SetMaterial(&OMaterial);
                
                OStaticMesh.Link();
                StaticMeshes.push_back(OStaticMesh);
                
                OStaticMesh = StaticMesh();
            }

            MaterialCount++;
            
            for(std::pair<std::string, std::string> MaterialData : MTL[Tokens[1]]) {
                if(MaterialData.first == "map_Kd") {
                    TextureFilepaths.push_back(std::make_pair<std::string, TextureType>(
                        FileDirectory + MaterialData.second,
                        TextureType::DIFFUSE
                    ));
                } else if(MaterialData.first == "map_d") {
                    TextureFilepaths.push_back(std::make_pair<std::string, TextureType>(
                        FileDirectory + MaterialData.second,
                        TextureType::TRANSPARENT
                    ));
                }
            }
        } else if(Tokens[0] == "o") {
            // Object name, you can use this if needed
        } else if(Tokens[0] == "mtllib") {
            std::string MTLFilepath = (FileDirectory + Tokens[1]);
            ParseMTL(MTLFilepath.c_str(), &MTL);
        }
        Tokens.clear();
    }
    
    for(std::pair<std::string, TextureType> TextureData : TextureFilepaths) {
        const char *StringType = "Diffuse";
        switch(TextureData.second) {
            case TextureType::DIFFUSE: {
                StringType = "Diffuse";
                break;
            }
            case TextureType::TRANSPARENT: {
                StringType = "Transparent";
                break;
            }
        }
        OMaterial.SetTexture(Texture(TextureData.first.c_str(), StringType, (uint32_t) TextureData.second), TextureData.second);
    }
    OStaticMesh.SetMaterial(&OMaterial);
    
    OStaticMesh.Link();
    StaticMeshes.push_back(OStaticMesh);
    bIsLoaded = true;
}