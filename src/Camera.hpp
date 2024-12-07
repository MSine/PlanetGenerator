#ifndef CAMERA_H
#define CAMERA_H


#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    Camera(float distance = 10.0f, float yaw = 0.0f, float pitch = 0.0f) : distance(distance), yaw(yaw), pitch(pitch) {
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // Constrain pitch to avoid flipping at the poles
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event
    void ProcessMouseScroll(bool isUp) {
        distance = isUp ? distance / zoomSpeed : distance * zoomSpeed;
        if (distance < minDistance)
            distance = minDistance;
        if (distance > maxDistance)
            distance = maxDistance;
        updateCameraVectors();
    }

private:
    void updateCameraVectors() {
        position.x = distance * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        position.y = distance * sin(glm::radians(pitch));
        position.z = distance * sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    }

    glm::vec3 target = glm::vec3(0.f);
    glm::vec3 position;
    float distance;    // Distance from the target
    float yaw;         // Horizontal rotation around the target
    float pitch;       // Vertical rotation, constrained to avoid poles
    float sensitivity = 0.2f;   // Mouse sensitivity for smoother movement
    float zoomSpeed = 1.1f;      // Speed of zooming in/out
    float minDistance = 2.f;
    float maxDistance = 50.f;
};
#endif

