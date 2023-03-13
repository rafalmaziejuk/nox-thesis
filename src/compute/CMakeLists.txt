set(NOX_COMPUTE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_api.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_api.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compute_program.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/compute.cpp
)

target_sources(nox PRIVATE ${NOX_COMPUTE_SRCS})

add_subdirectories()
