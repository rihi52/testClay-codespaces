#define CLAY_IMPLEMENTATION
#include "../clay.h"
#include "../clay_renderer_SDL2.c"

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "styles.h"

/*-------------------------------------------------------------------------------------------*
*                                     START COPY                                             *
*--------------------------------------------------------------------------------------------*/

const int FONT_ID_BODY_16 = 0;
const int FONT_ID_BODY_32 = 0;
Clay_Color COLOR_WHITE = { 255, 255, 255, 255};

static const Uint32 FONT_ID = 0;

static const Clay_Color COLOR_ORANGE    = (Clay_Color) {225, 138, 50, 255};
static const Clay_Color COLOR_BLUE      = (Clay_Color) {111, 173, 162, 255};
static const Clay_Color COLOR_LIGHT     = (Clay_Color) {224, 215, 210, 255};
static const Clay_Color COLOR_BLACK     = (Clay_Color) {0, 0, 0, 255};

// typedef struct app_state {
//     SDL_Window *window;
//     Clay_SDL3RendererData rendererData;
// } AppState;

// static inline Clay_Dimensions SDL_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *userData)
// {
//     TTF_Font **fonts = userData;
//     TTF_Font *font = fonts[config->fontId];
//     int width, height;

//     TTF_SetFontSize(font, config->fontSize);
//     if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height)) {
//         SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to measure text: %s", SDL_GetError());
//     }

//     return (Clay_Dimensions) { (float) width, (float) height };
// }

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

Clay_RenderCommandArray ClayRedBackgroundLayout(void)
{
    Clay_BeginLayout();

    Clay_Sizing layoutExpand = {
    .width = CLAY_SIZING_GROW(0),
    .height = CLAY_SIZING_GROW(0)
    };

    // Define one element that covers the whole screen
    CLAY(CLAY_ID("OuterContainer"), { ParentWindow, .backgroundColor = COLOR_WHITE}) {

        /* Center container start */
        CLAY(CLAY_ID("HeadLabelContainer"), { HeadLabelWindow,.cornerRadius = CLAY_CORNER_RADIUS(10), .backgroundColor = COLOR_WHITE}) {
            CLAY_TEXT(CLAY_STRING("GUIDNBATTER"), CLAY_TEXT_CONFIG(WindowLabel));
        };
        /* Start button start */
        CLAY(CLAY_ID("StartButton"), ButtonStyle) {
            CLAY_TEXT(CLAY_STRING("Start Encounter"), CLAY_TEXT_CONFIG(ButtonLabel));
        };

        /* Build button start */
        CLAY(CLAY_ID("BuildButton"), ButtonStyle) {
            CLAY_TEXT(CLAY_STRING("Build Encounter"), CLAY_TEXT_CONFIG(ButtonLabel)); 
        };

        /* Creature button start */
        CLAY(CLAY_ID("CreatureDatabaseButton"), ButtonStyle) {
            CLAY_TEXT(CLAY_STRING("Creature Database"), CLAY_TEXT_CONFIG(ButtonLabel));
        };

        /* Player button start */ 
        CLAY(CLAY_ID("PlayerDatabaseButton"), ButtonStyle) {
            CLAY_TEXT(CLAY_STRING("Player Database"), CLAY_TEXT_CONFIG(ButtonLabel));
            
        };

        /* Creature button start */
        CLAY(CLAY_ID("button"), {MainButton, .backgroundColor = Clay_Hovered() ? COLOR_BLUE : COLOR_ORANGE }) {
            CLAY_TEXT(CLAY_STRING("test"), CLAY_TEXT_CONFIG(ButtonLabel));
        };
    };

    return Clay_EndLayout();
}

/*-------------------------------------------------------------------------------------------*
*                                       END COPY                                             *
*--------------------------------------------------------------------------------------------*/

struct ResizeRenderData_ {
    SDL_Window* window;
    int windowWidth;
    int windowHeight;
    SDL_Renderer* renderer;
    SDL2_Font* fonts;
};
typedef struct ResizeRenderData_ ResizeRenderData;

int resizeRendering(void* userData, SDL_Event* event) {
    ResizeRenderData *actualData = userData;
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED) {
        SDL_Window* window          = actualData->window;
        int windowWidth             = actualData->windowWidth;
        int windowHeight            = actualData->windowHeight;
        SDL_Renderer* renderer      = actualData->renderer;
        SDL2_Font* fonts            = actualData->fonts;

        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        Clay_SetLayoutDimensions((Clay_Dimensions) { (float)windowWidth, (float)windowHeight });

        Clay_RenderCommandArray renderCommands = ClayRedBackgroundLayout()/*ClayVideoDemo_CreateLayout(&demoData)*/;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Clay_SDL2_Render(renderer, renderCommands, fonts);

        SDL_RenderPresent(renderer);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error: could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Error: could not initialize TTF: %s\n", TTF_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        fprintf(stderr, "Error: could not initialize IMG: %s\n", IMG_GetError());
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("resources/Roboto-Regular.ttf", 16);
    if (!font) {
        fprintf(stderr, "Error: could not load font: %s\n", TTF_GetError());
        return 1;
    }

    SDL2_Font fonts[1] = {};

    fonts[FONT_ID_BODY_16] = (SDL2_Font) {
        .fontId = FONT_ID_BODY_16,
        .font = font,
    };

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
  
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); //for antialiasing
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); //for antialiasing

    bool enableVsync = false;
    if(enableVsync){ renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);} //"SDL_RENDERER_ACCELERATED" is for antialiasing
    else{renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);}
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //for alpha blending

    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float)windowWidth, (float)windowHeight }, (Clay_ErrorHandler) { HandleClayErrors });

    Clay_SetMeasureTextFunction(SDL2_MeasureText, &fonts);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    
    ResizeRenderData userData = {
        window, // SDL_Window*
        windowWidth, // int
        windowHeight, // int
        renderer, // SDL_Renderer*
        fonts // SDL2_Font[1]
    };
    // add an event watcher that will render the screen while youre dragging the window to different sizes
    SDL_AddEventWatch(resizeRendering, &userData);
    
    while (true) {
        Clay_Vector2 scrollDelta = {};
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: { goto quit; }
                case SDL_MOUSEWHEEL: {
                    scrollDelta.x = event.wheel.x;
                    scrollDelta.y = event.wheel.y;
                    break;
                }
            }
        }
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
        printf("%f\n", deltaTime);

        int mouseX = 0;
        int mouseY = 0;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        Clay_Vector2 mousePosition = (Clay_Vector2){ (float)mouseX, (float)mouseY };
        Clay_SetPointerState(mousePosition, mouseState & SDL_BUTTON(1));

        Clay_UpdateScrollContainers(
            true,
            (Clay_Vector2) { scrollDelta.x, scrollDelta.y },
            deltaTime
        );
        
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        Clay_SetLayoutDimensions((Clay_Dimensions) { (float)windowWidth, (float)windowHeight });

        Clay_RenderCommandArray renderCommands = ClayRedBackgroundLayout();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Clay_SDL2_Render(renderer, renderCommands, fonts);

        SDL_RenderPresent(renderer);
    }

quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

