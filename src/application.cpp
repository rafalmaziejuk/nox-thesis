#include "debug/debug_helpers.h"

#include "utilities/timer.h"

#include <nox/application.h>
#include <nox/window.h>

#include <nox/assets/asset_manager.h>

#include <nox/compute/compute.h>

#include <nox/events/event_dispatcher.h>

#include <nox/renderer/renderer.h>

namespace NOX {

    Application *Application::s_instance = nullptr;

    Application::Application(const ApplicationSpecification &specification) : m_specification(specification) {
        NOX_ABORT_IF(s_instance != nullptr);
        s_instance = this;

        Logger::initialize();

        m_eventDispatcher.getWindowCloseEventDelegate().subscribe([this](const WindowCloseEvent &event) { m_isRunning = false; });
        m_eventDispatcher.getWindowResizeEventDelegate().subscribe([](const WindowResizeEvent &event) {
            Renderer::setViewportSize(event.getWidth(), event.getHeight());
        });

        m_window = Window::create(WindowSpecification(&m_eventDispatcher, m_specification.name));

        Renderer::initialize();
        Compute::initialize();
    }

    Application::~Application() {}

    void Application::run() {
        Timer timer;
        while (m_isRunning) {
            float timestep = timer.restart();
            update(timestep);
            m_window->update();
        }
    }

    void Application::update(float timestep) {
        onUpdate(timestep);
    }

    const char *ApplicationCommandLineArguments::operator[](uint8_t index) const {
        NOX_ASSERT_IF(index < 0 || index > argumentCount);
        return arguments[index];
    }

} // namespace NOX
