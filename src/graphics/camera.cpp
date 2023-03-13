#include <nox/graphics/camera.h>

#include <glm/gtx/transform.hpp>

namespace NOX {

    Camera::Camera(const CameraSpecification &specification) : m_specification(specification) {
        updateViewMatrix();
        updateProjectionMatrix();
    }

    void Camera::updateCameraVectors() {
        m_forward = glm::normalize(glm::vec3(cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw)),
                                             sin(glm::radians(m_pitch)),
                                             cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw))));
        m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_up = glm::cross(m_right, m_forward);
    }

    void Camera::updateViewMatrix() {
        updateCameraVectors();
        m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
    }

    void Camera::updateProjectionMatrix() {
        m_projectionMatrix = glm::perspective(glm::radians(m_specification.fov),
                                              m_specification.aspectRatio,
                                              m_specification.nearPlane,
                                              m_specification.farPlane);
    }

    void Camera::rotate(const glm::vec2 &rotation) {
        m_yaw += rotation.x;
        m_pitch = glm::clamp(m_pitch + rotation.y, -89.0f, 89.0f);
        updateViewMatrix();
    }

    void Camera::move(const glm::vec3 &movement) {
        m_position += movement;
        updateViewMatrix();
    }

} // namespace NOX
