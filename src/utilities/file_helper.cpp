#include "debug/debug_helpers.h"

#include "utilities/file_helper.h"

#include <nox/application.h>

#include <fstream>
#include <sstream>

namespace NOX {

    std::string FileHelper::getAbsolutePath(const std::filesystem::path &path) {
        auto workingDirectoryPath = std::filesystem::path(Application::get()->getSpecification().workingDirectoryPath).parent_path();
        auto absolutePath = (workingDirectoryPath / path).make_preferred();
        return absolutePath.string();
    }

    std::string FileHelper::getParentPath(const std::filesystem::path &path) {
        return path.parent_path().string();
    }

    std::string FileHelper::readFile(const std::filesystem::path &path) {
        auto absolutePath = getAbsolutePath(path);
        NOX_ASSERT_IF(!std::filesystem::exists(absolutePath) || !std::filesystem::is_regular_file(absolutePath), "Cannot open {0}", absolutePath);

        std::ifstream file(absolutePath, std::ios::in);
        std::stringstream fileStream;
        fileStream << file.rdbuf();

        return fileStream.str();
    }

} // namespace NOX
