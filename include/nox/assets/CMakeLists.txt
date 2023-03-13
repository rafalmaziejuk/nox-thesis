set(NOX_ASSETS_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/asset_factory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asset_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asset.h
)

target_sources(nox PRIVATE ${NOX_ASSETS_INCS})
