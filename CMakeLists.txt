cmake_minimum_required(VERSION 3.16)
project(hello C)

# ------------------------------
# Output directories
# ------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# ------------------------------
# SDL base libraries
# ------------------------------
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# ------------------------------
# SDL_ttf
# ------------------------------
if(EMSCRIPTEN)
    message(STATUS "Building for Emscripten — using vendored Freetype, disabling vendored HarfBuzz")
    set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
    set(SDLTTF_HARFBUZZ OFF CACHE BOOL "" FORCE)
else()
    message(STATUS "Building native — using system Freetype/Harfbuzz")
    set(SDLTTF_VENDORED OFF CACHE BOOL "" FORCE)
    set(SDLTTF_HARFBUZZ OFF CACHE BOOL "" FORCE)

    # System paths
    set(FREETYPE_INCLUDE_DIRS "/usr/include/freetype2")
    set(FREETYPE_LIBRARIES "/usr/lib/x86_64-linux-gnu/libfreetype.so")
    set(HARFBUZZ_INCLUDE_DIRS "/usr/include/harfbuzz")
    set(HARFBUZZ_LIBRARIES "/usr/lib/x86_64-linux-gnu/libharfbuzz.so")
endif()

add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# ------------------------------
# Emscripten target settings
# ------------------------------
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")

    # Your game executable
    add_executable(hello
        src/global.c
        src/main_window.c
        src/main.c
        src/styles.c
    )

    # Link SDL libraries
    target_link_libraries(hello PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
    )

    # Preload resources folder so fonts/images work in browser
    set_target_properties(hello PROPERTIES
        LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/resources@/resources"
    )

    # Optional: additional Emscripten settings
    target_link_options(hello PRIVATE
        "-sALLOW_MEMORY_GROWTH"
        "-sMAX_WEBGL_VERSION=2"
    )
else()
    # ------------------------------
    # Native target (Linux)
    # ------------------------------
    add_executable(hello
        src/global.c
        src/main_window.c
        src/main.c
        src/styles.c
    )

    target_link_libraries(hello PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        ${FREETYPE_LIBRARIES}
        ${HARFBUZZ_LIBRARIES}
    )

    target_include_directories(hello PRIVATE
        ${FREETYPE_INCLUDE_DIRS}
        ${HARFBUZZ_INCLUDE_DIRS}
    )
endif()