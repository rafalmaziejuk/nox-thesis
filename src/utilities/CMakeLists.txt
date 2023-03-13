set(NOX_UTILITIES_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/file_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_helper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer.h
)

target_sources(nox PRIVATE ${NOX_UTILITIES_SRCS})
