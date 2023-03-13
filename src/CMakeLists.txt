set(NOX_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
)

target_sources(nox PRIVATE ${NOX_SRCS})

add_subdirectories()
