#pragma once

#include <glm/glm.hpp>

namespace NOX {

    struct CameraSpecification {
        float aspectRatio{16.0f / 9.0f};
        float fov{45.0f};
        float nearPlane{0.1f};
        float farPlane{1000.0f};
    };

    class Camera {
      public:
        Camera(const CameraSpecification &specification = CameraSpecification());

        const CameraSpecification &getSpecification() const { return m_specification; }
        const glm::mat4 &getViewMatrix() const { return m_viewMatrix; }
        const glm::mat4 &getProjectionMatrix() const { return m_projectionMatrix; }
        const glm::vec3 &getForwardVector() const { return m_forward; }
        const glm::vec3 &getUpVector() const { return m_up; }
        const glm::vec3 &getRightVector() const { return m_right; }
        const glm::vec3 &getPosition() const { return m_position; }

        void rotate(const glm::vec2 &rotation);
        void move(const glm::vec3 &movement);

      private:
        void updateCameraVectors();
        void updateViewMatrix();
        void updateProjectionMatrix();

      private:
        CameraSpecification m_specification{};

        glm::vec3 m_position{0.0f};
        float m_yaw{-90.0f};
        float m_pitch{0.0f};

        glm::vec3 m_forward{0.0f, 0.0f, -1.0f};
        glm::vec3 m_up{0.0f, 1.0f, 0.0f};
        glm::vec3 m_right{0.0f, 0.0f, 0.0f};

        glm::mat4 m_viewMatrix{1.0f};
        glm::mat4 m_projectionMatrix{1.0f};
    };

} // namespace NOX
