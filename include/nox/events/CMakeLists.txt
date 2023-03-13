set(NOX_EVENTS_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/event_delegate.h
    ${CMAKE_CURRENT_SOURCE_DIR}/event_dispatcher.h
    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mouse_event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/window_event.h
)

target_sources(nox PRIVATE ${NOX_EVENTS_INCS})
