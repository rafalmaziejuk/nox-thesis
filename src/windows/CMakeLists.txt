set(NOX_WINDOWS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/windows_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/windows_window.h
)

target_sources(nox PRIVATE ${NOX_WINDOWS_SRCS})
