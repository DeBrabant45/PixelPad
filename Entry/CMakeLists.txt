# Entry Layer

add_executable(${PIXEL_PAD_ENTRY_TARGET_NAME}
    src/EntryPoint.cpp
    include/EntryPoint.hpp

    src/ApplicationComposer.cpp
    include/ApplicationComposer.hpp

    src/Main.cpp
)

target_include_directories(${PIXEL_PAD_ENTRY_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_ENTRY_TARGET_NAME}
   PRIVATE
        ${PIXEL_PAD_CORE_TARGET_NAME}
        ${PIXEL_PAD_APPLICATION_TARGET_NAME}
        ${PIXEL_PAD_PRESENTATION_TARGET_NAME}
        ${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
)
