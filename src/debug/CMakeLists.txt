set(NOX_DEBUG_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/debug_helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug_helpers.h
)

target_sources(nox PRIVATE ${NOX_DEBUG_SRCS})
