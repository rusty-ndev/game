#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(glm::vec3 position)
    : Position(position), Front(0.0f, 0.0f, -1.0f),
      WorldUp(0.0f, 1.0f, 0.0f), Yaw(-90.f), Pitch(0.f),
      Fov(45.f), MovementSpeed(2.5f), MouseSensitivity(0.1f)
{
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        Position += Front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        Position -= Front * velocity;
    if (direction == Camera_Movement::LEFT)
        Position -= Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
        Pitch = std::clamp(Pitch, -89.0f, 89.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}
