set(NOX_GRAPHICS_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/camera_controller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/image.h
    ${CMAKE_CURRENT_SOURCE_DIR}/light.h
    ${CMAKE_CURRENT_SOURCE_DIR}/model.h
)

target_sources(nox PRIVATE ${NOX_GRAPHICS_INCS})
