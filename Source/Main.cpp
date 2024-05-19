#include "Mesh.hpp"

int main(void)
{
    if(!glfwInit()) {
        return -1;
    }

    uint32_t Width = 1920;
    uint32_t Height = 1080;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    std::string WindowTitle = "Crafdead";

    GLFWwindow *Window = glfwCreateWindow(Width, Height, WindowTitle.c_str(), NULL, NULL);
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


    Vertex Vertices[] = {
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
    };

    uint32_t Indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    Vertex LightVertices[] = {
        Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
    };

    uint32_t LightIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };

    Texture Textures[]
	{
		Texture("Assets\\Image\\Planks.bmp", "Diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Assets\\Image\\PlanksSpecular.bmp", "Specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};


    Shader DefaultShader;
    DefaultShader.Create();
    DefaultShader.Load("Source\\Resource\\Shader\\Default.vert", ShaderType::VERTEX);
    DefaultShader.Load("Source\\Resource\\Shader\\Default.frag", ShaderType::FRAGMENT);
	
	std::vector<Vertex> VecVertices(Vertices, Vertices + sizeof(Vertices) / sizeof(Vertex));
	std::vector<uint32_t> VecIndices(Indices, Indices + sizeof(Indices) / sizeof(uint32_t));
	std::vector<Texture> VecTextures(Textures, Textures + sizeof(Textures) / sizeof(Texture));
	
    Mesh Floor(&VecVertices, &VecIndices, &VecTextures);

	Shader LightShader;
    LightShader.Create();
    LightShader.Load("Source\\Resource\\Shader\\Light.vert", ShaderType::VERTEX);
    LightShader.Load("Source\\Resource\\Shader\\Light.frag", ShaderType::FRAGMENT);
	
	std::vector<Vertex> VecLightVertices(LightVertices, LightVertices + sizeof(LightVertices) / sizeof(Vertex));
	std::vector<uint32_t> VecLightIndices(LightIndices, LightIndices + sizeof(LightIndices) / sizeof(uint32_t));
	
	Mesh Light(&VecLightVertices, &VecLightIndices, &VecTextures);

	glm::vec4 LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 LightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 LightModel = glm::mat4(1.0f);
	LightModel = glm::translate(LightModel, LightPos);

	glm::vec3 ObjectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 ObjectModel = glm::mat4(1.0f);
	ObjectModel = glm::translate(ObjectModel, ObjectPos);


	LightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(LightShader.Id, "model"), 1, GL_FALSE, glm::value_ptr(LightModel));
	glUniform4f(glGetUniformLocation(LightShader.Id, "lightColor"), LightColor.x, LightColor.y, LightColor.z, LightColor.w);
	DefaultShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(DefaultShader.Id, "model"), 1, GL_FALSE, glm::value_ptr(ObjectModel));
	glUniform4f(glGetUniformLocation(DefaultShader.Id, "lightColor"), LightColor.x, LightColor.y, LightColor.z, LightColor.w);
	glUniform3f(glGetUniformLocation(DefaultShader.Id, "lightPos"), LightPos.x, LightPos.y, LightPos.z);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    Camera MainCamera(Width, Height, glm::vec3(0.0f, 0.0f, 2.0f));

    double CurrentTime = 0.0;
    double PreviouseTime = 0.0;
    double TimeDifference = 0.0;
    uint32_t FrameCounter = 0;

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

		Floor.Draw(&DefaultShader, &MainCamera);
		Light.Draw(&LightShader, &MainCamera);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    DefaultShader.Delete();
	LightShader.Delete();
    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
