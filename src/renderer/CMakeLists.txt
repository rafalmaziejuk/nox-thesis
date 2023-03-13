set(NOX_RENDERER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/buffer_layout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/element_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer_api.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer_api.h
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer_context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertex_buffer.cpp
)

target_sources(nox PRIVATE ${NOX_RENDERER_SRCS})

add_subdirectories()
