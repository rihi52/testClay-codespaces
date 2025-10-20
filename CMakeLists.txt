cmake_minimum_required(VERSION 3.16)
project(hello)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL#
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# on Web targets, we need CMake to generate a HTML webpage. 
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

# Create your game executable target as usual
add_executable(hello WIN32 src/global.c src/main_window.c src/main.c src/styles.c)

# Link to the actual SDL3 library.
target_link_libraries(hello PRIVATE SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image SDL3::SDL3)

# cmake_minimum_required(VERSION 3.20)
# project(clay_sdl2_video_demo C)

# set(CMAKE_C_STANDARD 11)

# # --- Sources ---
# set(SOURCES
#     src/main.c
#     # clay_renderer_SDL2.c
#     # shared-layouts/clay-video-demo.c
# )

# add_executable(clay_sdl2_video_demo ${SOURCES})

# # --- Emscripten settings ---
# set(CMAKE_EXECUTABLE_SUFFIX ".html")
# set(RESOURCE_PATH "${CMAKE_SOURCE_DIR}/resources")
# set(PRELOAD_FLAG "--preload-file ${RESOURCE_PATH}@/resources")

# # This is the magic: add the flags to COMPILE_FLAGS and LINK_FLAGS
# set_target_properties(clay_sdl2_video_demo PROPERTIES
#     COMPILE_FLAGS "-sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sALLOW_MEMORY_GROWTH=1 -sWASM=1 -sASYNCIFY"
#     LINK_FLAGS "-sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sALLOW_MEMORY_GROWTH=1 -sWASM=1 -sASYNCIFY ${PRELOAD_FLAG}"
# )
