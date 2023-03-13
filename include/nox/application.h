#pragma once

#include <nox/assets/asset_manager.h>

#include <nox/events/event_dispatcher.h>

#include <memory>
#include <string>

namespace NOX {

    struct ApplicationCommandLineArguments {
        int argumentCount{0};
        char **arguments{nullptr};

        const char *operator[](uint8_t index) const;
    };

    struct ApplicationSpecification {
        ApplicationCommandLineArguments arguments;
        std::string name;
        std::string workingDirectoryPath;
    };

    class Window;

    class Application {
      public:
        Application(const ApplicationSpecification &specification);
        virtual ~Application();

        static Application *get() { return s_instance; }
        const ApplicationSpecification &getSpecification() const { return m_specification; }

        const AssetManager &getAssetManager() const { return m_assetManager; }
        AssetManager &getAssetManager() { return m_assetManager; }

        const EventDispatcher &getEventDispatcher() const { return m_eventDispatcher; }
        EventDispatcher &getEventDispatcher() { return m_eventDispatcher; }

        const Window &getWindow() const { return *m_window; }

      public:
        virtual void onUpdate(float timestep) = 0;

        void run();
        void update(float timestep);

      protected:
        AssetManager m_assetManager{};
        EventDispatcher m_eventDispatcher{};
        std::unique_ptr<Window> m_window{nullptr};

      private:
        bool m_isRunning{true};
        ApplicationSpecification m_specification;

        static Application *s_instance;
    };

} // namespace NOX
