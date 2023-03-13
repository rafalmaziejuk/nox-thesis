set(NOX_OPENGL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_built_in_shaders.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_element_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_element_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_framebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_helper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_vertex_array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_vertex_array.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_vertex_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gl_vertex_buffer.h
)

target_sources(nox PRIVATE ${NOX_OPENGL_SRCS})
