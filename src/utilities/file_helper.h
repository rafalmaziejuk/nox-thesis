#pragma once

#include <filesystem>
#include <string>

namespace NOX {

    class FileHelper {
      public:
        [[nodiscard]] static std::string getAbsolutePath(const std::filesystem::path &path);
        [[nodiscard]] static std::string getParentPath(const std::filesystem::path &path);
        [[nodiscard]] static std::string readFile(const std::filesystem::path &path);
    };

} // namespace NOX
