#include "Model.hpp"

void Model::Draw(Shader *OShader, Camera *OCamera)
{
    for (StaticMesh OStaticMesh : StaticMeshes) {
        OShader->Activate();
        OStaticMesh.GetMaterial()->BindAll(OShader);
        
        glUniform3f(glGetUniformLocation(OShader->GetId(), "CameraPosition"), OCamera->Position.x, OCamera->Position.y, OCamera->Position.z);
        OCamera->Matrix(OShader, "CameraMatrix");
        
        OStaticMesh.Draw();
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

void Model::ParseMTL(const char *Filepath, std::unordered_map<std::string, std::string> *MTL)
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
        } else if(Tokens[0] == "map_Kd") {
            if(FoundKey) {
                (*MTL)[CurrentKey] = Tokens[1];
                std::cout << CurrentKey << " " << Tokens[1] << std::endl;
                CurrentKey = "";
                FoundKey = false;
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

    std::unordered_map<std::string, std::string> MTL;
    std::vector<std::string> Tokens;
    std::string Line;

    bool HasMaterial = false;
    Material OMaterial;
    std::unordered_map<uint32_t,uint32_t> VIM;

    std::string TextureFilepath;
    while (std::getline(File, Line)) {
        Split(&Line, &Tokens, ' ');
        if(Tokens.empty());

        if(Tokens[0] == "f") {
            std::vector<std::string> FaceTokens;
            for(uint32_t i = 1; i < 4; ++i) {
                Split(&Tokens[i], &FaceTokens, '/');
                uint32_t ModelIndex = std::stoi(FaceTokens[0]); 
                uint32_t RealIndex;
                if(VIM.find(ModelIndex) != VIM.end()) {
                    RealIndex = VIM[ModelIndex];
                } else {
                    RealIndex = OStaticMesh.GetVerticesSize();
                    VIM[ModelIndex] = RealIndex;
                    Vertex OVertex;
                    OVertex.Position = Vertices[std::stoi(FaceTokens[0]) - 1];
                    OVertex.Normal = Normals[std::stoi(FaceTokens[2]) - 1];
                    OVertex.UV = UVs[std::stoi(FaceTokens[1]) - 1];
                    
                    OStaticMesh.AddVertex(OVertex);
                }
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
            TextureFilepath = (FileDirectory + MTL[Tokens[1]]);
            if (HasMaterial) {
                StaticMeshes.push_back(OStaticMesh);
                
                OStaticMesh = StaticMesh();
                
                OMaterial.SetTexture(Texture(TextureFilepath.c_str(), "Diffuse", 0));
                std::cout << TextureFilepath.c_str() << std::endl;
                OStaticMesh.SetMaterial(&OMaterial);
                
                OStaticMesh.Link();
            } else {
                HasMaterial = true;
            }

            VIM.clear();
        } else if(Tokens[0] == "o") {
            // Object name, you can use this if needed
        } else if(Tokens[0] == "mtllib") {
            std::string MTLFilepath = (FileDirectory + Tokens[1]);
            ParseMTL(MTLFilepath.c_str(), &MTL);
        }
        Tokens.clear();
    }
    
    OMaterial.SetTexture(Texture(TextureFilepath.c_str(), "Diffuse", 0));
    std::cout << TextureFilepath.c_str() << std::endl;
    OStaticMesh.SetMaterial(&OMaterial);
    
    OStaticMesh.Link();

    StaticMeshes.push_back(OStaticMesh);
    bIsLoaded = true;
}