#include "Camera.hpp"

Camera::Camera(int32_t Width, int32_t Height, glm::vec3 Position)
{
    Camera::Width = Width;
    Camera::Height = Height;
    Camera::Position = Position;
}

void Camera::UpdateMatrix(float FOV, float NearPlane, float FarPlane)
{
    glm::mat4 View = glm::mat4(1.0f);
    glm::mat4 Projection = glm::mat4(1.0f);

    View = glm::lookAt(Position, Position + Orientation, UpVector);
    Projection = glm::perspective(
        glm::radians(FOV),
        (float) Width / (float) Height,
        NearPlane,
        FarPlane
    );

    CameraMatrix = Projection * View;
}

void Camera::Matrix(Shader *OShader, const char *Uniform)
{
    uint32_t TargetLocation = glGetUniformLocation(
        OShader->GetId(),
        Uniform
    );
    glUniformMatrix4fv(TargetLocation, 1, GL_FALSE, glm::value_ptr(CameraMatrix));
}

void Camera::Inputs(GLFWwindow *Window)
{
    if(glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) {
        Position += Speed * Orientation;
    } else if(glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS) {
        Position += Speed * -Orientation;
    }
    if(glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS) {
        Position += Speed * -glm::normalize(glm::cross(Orientation, UpVector));
    } else if(glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS) {
        Position += Speed * glm::normalize(glm::cross(Orientation, UpVector));
    }
    if(glfwGetKey(Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        Position += Speed * UpVector;
    } else if(glfwGetKey(Window, GLFW_KEY_C) == GLFW_PRESS) {
        Position += Speed * -UpVector;
    }
    if(glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        Speed = SprintSpeed;
    } else if(glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        Speed = WalkSpeed;
    }

    if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if(!IsPressed) {
            glfwSetCursorPos(Window, (Width / 2.0f), (Height / 2.0f));
            IsPressed = true;
        }

        double MouseX;
        double MouseY;
        glfwGetCursorPos(Window, &MouseX, &MouseY);

        float RotationX = Sensitivity * (float)(MouseY - (Height / 2.0f)) / Height;
        float RotationY = Sensitivity * (float)(MouseX - (Width / 2.0f)) / Width;

        glm::vec3 NewOrentation = glm::rotate(
            Orientation,
            glm::radians(-RotationX),
            glm::normalize(glm::cross(Orientation, UpVector))
        );

        if(!(((glm::angle(NewOrentation, UpVector)) <= glm::radians(5.0f) || glm::angle(NewOrentation, UpVector)) <= glm::radians(-5.0f))) {
            Orientation = NewOrentation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-RotationY), UpVector);

        glfwSetCursorPos(Window, (Width / 2.0f), (Height / 2.0f));
    } else if(glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        IsPressed = false;
    }
}