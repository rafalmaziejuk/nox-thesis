set(NOX_GRAPHICS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/assimp_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/assimp_helper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camera_controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/light.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
)

target_sources(nox PRIVATE ${NOX_GRAPHICS_SRCS})
