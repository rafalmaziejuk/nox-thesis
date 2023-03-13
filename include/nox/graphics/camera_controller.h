#pragma once

#include <nox/graphics/camera.h>

#include <memory>

namespace NOX {

    class CameraController {
      public:
        enum class Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            FORWARDS,
            BACKWARDS
        };

      public:
        CameraController();
        ~CameraController();

        const Camera &getCamera() const { return m_camera; }
        bool isFocused() const { return m_isFocused; }

        void focus();
        void rotate(const float sensitivity);
        void move(const Direction direction, const float speed);

      private:
        Camera m_camera{};
        bool m_isFocused{false};
    };

} // namespace NOX
