set(NOX_OPENCL_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_command_queue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_command_queue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_compute.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_compute.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_device.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_helper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_image.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_kernel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_program.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_program.h
)

target_sources(nox PRIVATE ${NOX_OPENCL_SRCS})
