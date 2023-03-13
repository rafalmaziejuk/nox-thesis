
#include <nox/application.h>
#include <nox/input.h>
#include <nox/input_identifiers.h>
#include <nox/window.h>

#include <nox/graphics/camera.h>
#include <nox/graphics/camera_controller.h>

namespace NOX {

    namespace {

        CursorPosition lastCursorPosition;

    } // namespace

    CameraController::CameraController() {
        lastCursorPosition = Input::getCursorPosition();
    }

    CameraController::~CameraController() {}

    void CameraController::focus() {
        m_isFocused = !m_isFocused;

        const auto &window = Application::get()->getWindow();
        auto centerX = static_cast<float>(window.getWidth()) / 2.0f;
        auto centerY = static_cast<float>(window.getHeight()) / 2.0f;
        window.setCursorPosition({centerX, centerY});
        window.setCursorMode(m_isFocused ? CursorMode::DISABLED : CursorMode::NORMAL);

        lastCursorPosition = {centerX, centerY};
    }

    void CameraController::rotate(const float sensitivity) {
        if (m_isFocused) {
            auto currentCursorPosition = Input::getCursorPosition();
            auto deltaX = (currentCursorPosition.x - lastCursorPosition.x) * sensitivity;
            auto deltaY = (-currentCursorPosition.y + lastCursorPosition.y) * sensitivity;
            lastCursorPosition = currentCursorPosition;
            m_camera.rotate({deltaX, deltaY});
        }
    }

    void CameraController::move(const Direction direction, const float speed) {
        if (m_isFocused) {
            glm::vec3 movement{};
            switch (direction) {
            case Direction::UP:
                movement += (m_camera.getUpVector() * speed);
                break;

            case Direction::DOWN:
                movement -= (m_camera.getUpVector() * speed);
                break;

            case Direction::LEFT:
                movement -= (m_camera.getRightVector() * speed);
                break;

            case Direction::RIGHT:
                movement += (m_camera.getRightVector() * speed);
                break;

            case Direction::FORWARDS:
                movement += (m_camera.getForwardVector() * speed);
                break;

            case Direction::BACKWARDS:
                movement -= (m_camera.getForwardVector() * speed);
                break;
            }
            m_camera.move(movement);
        }
    }

} // namespace NOX
