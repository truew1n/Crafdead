#ifndef CFD_CAMERA_H
#define CFD_CAMERA_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 CameraMatrix = glm::mat4(1.0f);

    bool IsPressed = false;

    int32_t Width;
    int32_t Height;

    const float WalkSpeed = 0.01f;
    const float SprintSpeed = 0.03f;

    float Speed = 0.1f;
    float Sensitivity = 300.0f;

    Camera(int32_t Width, int32_t Height, glm::vec3 Position);

    void UpdateMatrix(float FOV, float NearPlane, float FarPlane);
    void Matrix(Shader *OShader, const char *Uniform);
    void Inputs(GLFWwindow *Window);
};
#endif