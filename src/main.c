#define CLAY_IMPLEMENTATION
#include "../clay.h"
#include "../clay_renderer_SDL2.c"

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

/*-------------------------------------------------------------------------------------------*
*                                     START COPY                                             *
*--------------------------------------------------------------------------------------------*/

const int FONT_ID_BODY_16 = 0;

static const Uint32 FONT_ID = 0;

const Clay_LayoutConfig ParentWindow = (Clay_LayoutConfig) {
    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)},
    .padding = { 16, 16, 16, 16},
    .childGap = 16,
    .childAlignment =  { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
    .layoutDirection = CLAY_LEFT_TO_RIGHT
};

Clay_RenderCommandArray ClayRedBackgroundLayout(void)
{
    Clay_BeginLayout();

    Clay_Sizing layoutExpand = {
    .width = CLAY_SIZING_GROW(0),
    .height = CLAY_SIZING_GROW(0)
    };

    // Define one element that covers the whole screen
    CLAY(CLAY_ID("OuterContainer"), {
        ParentWindow,
        .backgroundColor = { 50, 50, 50, 255 }
    }) {/* Center container start */
        CLAY(CLAY_ID("CenterContainer"), {
        ParentWindow,
        .cornerRadius = CLAY_CORNER_RADIUS(25),
        .backgroundColor = { 100, 100, 100, 255 }
        }) {/* Build button start */
            CLAY(CLAY_ID("BuildButton"), {
            .layout = { .padding = { 16, 16, 8, 8 }},
            .backgroundColor = {85, 255, 85, 255 },
            .cornerRadius = CLAY_CORNER_RADIUS(15)
            }) {
                CLAY_TEXT(CLAY_STRING("Build Encounter"), CLAY_TEXT_CONFIG({
                    .fontId = FONT_ID_BODY_16,
                    .fontSize = 16,
                    .textColor = { 0, 0, 0, 255}
                }));
            }/* Build button end */ 
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

