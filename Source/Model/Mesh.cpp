#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> *Vertices, std::vector<uint32_t> *Indices, std::vector<Texture> *Textures)
{
    Mesh::Vertices = *Vertices;
	Mesh::Indices = *Indices;
	Mesh::Textures = *Textures;

	OVertexArray.Bind();
	
	VertexBuffer OVertexBuffer(Vertices);
	ElementBuffer OElementBuffer(Indices);
	
	OVertexArray.LinkAttrib(&OVertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	OVertexArray.LinkAttrib(&OVertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	OVertexArray.LinkAttrib(&OVertexBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	OVertexArray.LinkAttrib(&OVertexBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	
	OVertexArray.Unbind();
	OVertexBuffer.Unbind();
	OElementBuffer.Unbind();
}

void Mesh::Draw(Shader *OShader, Camera *OCamera)
{
	OShader->Activate();
	OVertexArray.Bind();

	uint32_t DiffuseCount = 0;
	uint32_t SpecularCount = 0;

	for (uint32_t i = 0; i < Textures.size(); i++)
	{
		std::string Num;
		std::string Type = Textures[i].Type;
		if (Type == "Diffuse")
		{
			Num = std::to_string(DiffuseCount++);
		}
		else if (Type == "Specular")
		{
			Num = std::to_string(SpecularCount++);
		}
		Textures[i].TexUnit(OShader, (Type + Num).c_str(), i);
		Textures[i].Bind();
	}
	
	glUniform3f(glGetUniformLocation(OShader->Id, "CameraPosition"), OCamera->Position.x, OCamera->Position.y, OCamera->Position.z);
	OCamera->Matrix(OShader, "CameraMatrix");

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
}