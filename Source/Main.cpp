#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.hpp"

#include "Shader.hpp"

#include "Camera.hpp"

int main(void)
{
    if(!glfwInit()) {
        return -1;
    }

    uint32_t Width = 1920;
    uint32_t Height = 1080;

    GLFWwindow *Window = glfwCreateWindow(Width, Height, "3 Days to Die", NULL, NULL);
    if(!Window) {
        fprintf(stderr, "Failed to create GLFW Window!\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(Window);

    glfwSwapInterval(1);
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Glew failed to initialize!\n");
        return -1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));


    float positions[] = {
        -0.5f, 0.0f, 0.5f,      0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,      5.0f, 0.0f,
        0.5f, 0.0f, -0.5f,      0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,      5.0f, 0.0f,
        0.0f, 0.8f, 0.0f,      2.5f, 5.0f
    };

    uint32_t indecies[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    uint32_t buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 25 * sizeof(float), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    uint32_t indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18 * sizeof(uint32_t), indecies, GL_STATIC_DRAW);

    Shader DefaultShader = Shader();
    DefaultShader.Create();
    DefaultShader.Load("Source\\Resource\\Shader\\Basic.vert", ShaderType::VERTEX);
    DefaultShader.Load("Source\\Resource\\Shader\\Basic.frag", ShaderType::FRAGMENT);
    DefaultShader.Activate();

    bmp_t BrickTexture = open_bmp("Assets\\Image\\Bricks.bmp");

    uint32_t Textures;
    glGenTextures(1, &Textures);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Textures);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BrickTexture.width, BrickTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, BrickTexture.memory);

    free(BrickTexture.memory);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGenerateMipmap(GL_TEXTURE_2D);

    uint32_t location = glGetUniformLocation(DefaultShader.Id, "Tex0");
    assert(location != -1);
    glUniform1i(location, 0);

    glEnable(GL_DEPTH_TEST);

    Camera MainCamera(Width, Height, glm::vec3(0.0f, 0.0f, 2.0f));

    while(!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainCamera.Inputs(Window);
        MainCamera.UpdateMatrix(60.0f, 0.1f, 100.0f);
        MainCamera.Matrix(&DefaultShader, "CameraMatrix");

        glBindTexture(GL_TEXTURE_2D, Textures);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    glDeleteTextures(1, &Textures);
    DefaultShader.Delete();
    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
