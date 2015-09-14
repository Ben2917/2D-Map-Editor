

file(GLOB SRCS *.cpp *.h)

set(BIN_DIR ${map_editor_SOURCE_DIR}/bin)

add_executable(map_editor ${SRCS})

target_link_libraries(map_editor ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS map_editor RUNTIME DESTINATION ${BIN_DIR})
