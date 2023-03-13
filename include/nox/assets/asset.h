#pragma once

#include <filesystem>
#include <string_view>

namespace NOX {

    class Asset {
      public:
        virtual ~Asset() = default;

        void setName(std::string_view name) {
            m_name = name;
        }

        const std::string &getName() const {
            return m_name;
        }

        virtual void reload() {}

        bool isReloadable() const {
            return m_isReloadable;
        }

        bool isDirty() const {
            if (m_timestamp < std::filesystem::last_write_time(m_path)) {
                return true;
            }
            return false;
        }

        void updateTimestamp() {
            m_timestamp = std::filesystem::last_write_time(m_path);
        }

      protected:
        std::filesystem::file_time_type m_timestamp{};
        bool m_isReloadable{false};
        std::string m_path{};
        std::string m_name;
    };

} // namespace NOX
