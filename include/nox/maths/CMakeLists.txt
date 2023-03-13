set(NOX_MATHS_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/bounding_box.h
)

target_sources(nox PRIVATE ${NOX_MATHS_INCS})
