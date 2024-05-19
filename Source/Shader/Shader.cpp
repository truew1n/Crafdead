#include "Shader.hpp"


uint8_t Shader::Load(const char *Filepath, ShaderType Type)
{
    FILE* File = fopen(Filepath, "rb");
    if (File == NULL) {
        fprintf(stderr, "Error opening file %s\n", Filepath);
        return 0;
    }

    fseek(File, 0, SEEK_END);
    long FileSize = ftell(File);
    fseek(File, 0, SEEK_SET);

    char *Content = (char*)malloc(FileSize + 1);
    if (Content == NULL) {
        fclose(File);
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    size_t BytesRead = fread(Content, 1, FileSize, File);
    if (BytesRead < FileSize) {
        fclose(File);
        free(Content);
        fprintf(stderr, "Error reading File %s\n", Filepath);
        return 0;
    }

    Content[FileSize] = '\0';

    fclose(File);

    uint32_t ShaderId = Compile(Content, Type);

    if(!ShaderId) {
        free(Content);
        return 0;
    }

    glAttachShader(Id, ShaderId);
    glLinkProgram(Id);
    glValidateProgram(Id);

    glDeleteShader(ShaderId);

    free(Content);
    return 1;
}

uint32_t Shader::Compile(const char *Source, ShaderType Type)
{
    uint32_t GLType = GL_VERTEX_SHADER;
    switch(Type) {
        case ShaderType::VERTEX: {
            GLType = GL_VERTEX_SHADER;
            break;
        }
        case ShaderType::FRAGMENT: {
            GLType = GL_FRAGMENT_SHADER;
            break;
        }
    }
    uint32_t ShaderId = glCreateShader(GLType);
    glShaderSource(ShaderId, 1, &Source, nullptr);
    glCompileShader(ShaderId);

    int32_t Result;
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Result);
    if(!Result) {
        int32_t Length;
        glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &Length);
        char *Message = (char *) malloc(Length * sizeof(char));
        glGetShaderInfoLog(ShaderId, Length, &Length, Message);
        printf(
            "Failed to compile %s shader!\n%s\n",
            (GLType == GL_VERTEX_SHADER ? "vertex" : "fragment"),
            Message
        );
        free(Message);
        glDeleteShader(ShaderId);
        return 0;
    }

    return ShaderId;
}

void Shader::Create()
{
    Id = glCreateProgram();
}

void Shader::Activate()
{
    glUseProgram(Id);
}

void Shader::Delete()
{
    glDeleteShader(Id);
}