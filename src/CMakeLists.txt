include_directories(${CMAKEDEMO_SOURCE_DIR}/src)
link_directories(${CMAKEDEMO_BINARY_DIR}/src)

find_package(OpenGL)

add_executable(${PROJECT_NAME}
    flex.cpp
    engine/engine.cpp
    engine/texture.cpp
    log/log.cpp
    util/fps.cpp
)

target_link_libraries(${PROJECT_NAME}
    m
    SDL2
    ${OPENGL_LIBRARY}
)
