# assimp
set(BUILD_SHARED_LIBS            OFF CACHE INTERNAL "")
set(ASSIMP_BUILD_ASSIMP_TOOLS    OFF CACHE INTERNAL "")
set(ASSIMP_BUILD_TESTS           OFF CACHE INTERNAL "")
set(ASSIMP_INSTALL               OFF CACHE INTERNAL "")
set(ASSIMP_INJECT_DEBUG_POSTFIX  OFF CACHE INTERNAL "")
set(ASSIMP_INSTALL_PDB           OFF CACHE INTERNAL "")
set(ASSIMP_BUILD_ASSIMP_VIEW     OFF CACHE INTERNAL "")
add_subdirectory(assimp)
set_target_properties(
    assimp
    zlibstatic
    UpdateAssimpLibsDebugSymbolsAndDLLs
    PROPERTIES FOLDER assimp
)

# GLAD
add_subdirectory(glad)
set_target_properties(
    glad
    PROPERTIES FOLDER glad
)

# GLFW
add_subdirectory(glfw)
set(GLFW_BUILD_EXAMPLES  OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS     OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS      OFF CACHE INTERNAL "")
set(GLFW_INSTALL         OFF CACHE INTERNAL "")
set_target_properties(
    glfw
    update_mappings
    PROPERTIES FOLDER glfw
)

# glm
add_subdirectory(glm)

# OpenCL
find_package(OpenCL REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)

# spdlog
add_subdirectory(spdlog)
set_target_properties(
    spdlog
    PROPERTIES FOLDER spdlog
)

# stb_image
add_subdirectory(stb_image)
set_target_properties(
    stb_image
    PROPERTIES FOLDER stb_image
)

target_link_libraries(nox
    PRIVATE
    assimp
    glad
    glfw
    OpenCL::OpenCL
    OpenGL::GL
    spdlog
    stb_image
    PUBLIC
    glm
)
