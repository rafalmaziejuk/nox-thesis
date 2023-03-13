set(NOX_MATHS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/bounding_box.cpp
)

target_sources(nox PRIVATE ${NOX_MATHS_SRCS})
