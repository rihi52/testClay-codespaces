cmake_minimum_required(VERSION 3.20)
project(clay_sdl2_video_demo C)

set(CMAKE_C_STANDARD 11)

# --- Sources ---
set(SOURCES
    SDL2-video-demo/main.c
    clay_renderer_SDL2.c
    shared-layouts/clay-video-demo.c
)

add_executable(clay_sdl2_video_demo ${SOURCES})

# --- Emscripten settings ---
set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(RESOURCE_PATH "${CMAKE_SOURCE_DIR}/SDL2-video-demo/resources")
set(PRELOAD_FLAG "--preload-file ${RESOURCE_PATH}@/resources")

# This is the magic: add the flags to COMPILE_FLAGS and LINK_FLAGS
set_target_properties(clay_sdl2_video_demo PROPERTIES
    COMPILE_FLAGS "-sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sALLOW_MEMORY_GROWTH=1 -sWASM=1 -sASYNCIFY"
    LINK_FLAGS "-sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sALLOW_MEMORY_GROWTH=1 -sWASM=1 -sASYNCIFY ${PRELOAD_FLAG}"
)
