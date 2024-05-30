#include "Model.hpp"

void ResizeCallback(GLFWwindow *Window, int32_t FrameBufferWidth, int32_t FrameBufferHeight)
{
    glViewport(0, 0, FrameBufferWidth, FrameBufferHeight);
}

int main(void)
{
    if(!glfwInit()) {
        return -1;
    }

    uint32_t Width = 1920;
    uint32_t Height = 1080;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    std::string WindowTitle = "Crafdead";

    GLFWwindow *Window = glfwCreateWindow(Width, Height, WindowTitle.c_str(), NULL, NULL);
    if(!Window) {
        fprintf(stderr, "Failed to create GLFW Window!\n");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(Window, ResizeCallback);
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(0);

    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Glew failed to initialize!\n");
        return -1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));


    Shader DefaultShader;
    DefaultShader.Create();
    DefaultShader.Load("Source\\Resource\\Shader\\Default.vert", ShaderType::VERTEX);
    DefaultShader.Load("Source\\Resource\\Shader\\Default.frag", ShaderType::FRAGMENT);

	glm::vec3 ObjectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 ObjectModel = glm::mat4(1.0f);
	ObjectModel = glm::translate(ObjectModel, ObjectPos);

	DefaultShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(DefaultShader.GetId(), "Model"), 1, GL_FALSE, glm::value_ptr(ObjectModel));

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    Camera MainCamera(Width, Height, glm::vec3(0.0f, 0.0f, 2.0f));

    Model YuccaModel;
    YuccaModel.LoadOBJ("Assets\\Models\\Yucca\\model.obj");

    double CurrentTime = 0.0;
    double PreviouseTime = 0.0;
    double TimeDifference = 0.0;
    uint32_t FrameCounter = 0;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(Window)) {
        CurrentTime = glfwGetTime();
        TimeDifference = CurrentTime - PreviouseTime;
        FrameCounter++;
        if(TimeDifference >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / TimeDifference) * FrameCounter);
            std::string MS = std::to_string((TimeDifference / FrameCounter) * 1000.0);
            std::string NewWindowTitle = WindowTitle + " - " + FPS + "FPS / " + MS + "ms";
            glfwSetWindowTitle(Window, NewWindowTitle.c_str());
            PreviouseTime = CurrentTime;
            FrameCounter = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainCamera.Inputs(Window);
		MainCamera.UpdateMatrix(45.0f, 0.1f, 100.0f);

        YuccaModel.Draw(&DefaultShader, &MainCamera);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
