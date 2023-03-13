set(NOX_RENDERER_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/buffer_layout.h
    ${CMAKE_CURRENT_SOURCE_DIR}/element_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/framebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vertex_buffer.h
)

target_sources(nox PRIVATE ${NOX_RENDERER_INCS})
