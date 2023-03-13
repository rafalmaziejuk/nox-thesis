set(NOX_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/input_identifiers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/input.h
    ${CMAKE_CURRENT_SOURCE_DIR}/window.h
)

target_sources(nox PRIVATE ${NOX_INCS})

add_subdirectories()
