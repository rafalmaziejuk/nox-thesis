set(NOX_COMPUTE_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_image.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_kernel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_program.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compute.h
)

target_sources(nox PRIVATE ${NOX_COMPUTE_INCS})
