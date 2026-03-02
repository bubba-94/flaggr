#include "flaggr.h"
#include <stdio.h>

/*
    Animation/Effects

    Make flags fade in/out, “wave,” or highlight a cross dynamically.

    This keeps FlagSpec data-driven while adding visual polish.

    Responsive Layouts

    Instead of fixed width/height, compute flag sizes based on window dimensions.

    Makes your engine scale to any screen.

    External Data Loading

    Store flag definitions in a file (JSON, CSV, or custom format) and load at runtime.

    This removes the need to recompile when adding flags.

    GUI or Menu Layer

    Add a small UI to select flags instead of just arrow keys.

    Prepares your engine for more complex interactions.
*/

int main(void) {
    App App = {0};

    int running = 1;

    // Add flags to this array
    static const FlagSpec FLAGS[] = {
        {"Sweden"       , 2, FLAG_NORDIC,       {BLUE, YELLOW}},
        {"Norway"       , 3, FLAG_NORDIC,       {RED, WHITE, BLUE}},
        {"Denmark"      , 2, FLAG_NORDIC,       {RED, WHITE}},
        {"Finland"      , 2, FLAG_NORDIC,       {WHITE, BLUE}},
        {"Iceland"      , 3, FLAG_NORDIC,       {BLUE, WHITE, RED}},
        {"Faroe Islands", 3, FLAG_NORDIC,       {WHITE, RED, BLUE}},
        {"Estonia"      , 3, FLAG_HORIZONTAL,   {BLUE, BLACK, WHITE}},
        {"Lithuania"    , 3, FLAG_HORIZONTAL,   {DARK_YELLOW, DARK_GREEN, DARK_RED}},
        {"Germany"      , 3, FLAG_HORIZONTAL,   {BLACK, RED, YELLOW}},
        {"Russia"       , 3, FLAG_HORIZONTAL,   {WHITE, BLUE, RED}},
        {"Luxembourg"   , 3, FLAG_HORIZONTAL,   {RED, WHITE, LIGHT_BLUE}},
        {"Poland"       , 2, FLAG_HORIZONTAL,   {RED, WHITE}},
        {"Hungary"      , 3, FLAG_HORIZONTAL,   {RED, WHITE, DARK_GREEN}},
        {"Armenia"      , 3, FLAG_HORIZONTAL,   {RED, BLUE, DARK_YELLOW}}
    };

    size_t len = sizeof(FLAGS) / sizeof(FLAGS[0]);
    
    if (!init(&App, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT)) return 1;
    
    size_t index = 0;

    while (running){

        // Register event
        SDL_Event event;

        while (SDL_PollEvent(&event) || index != len){
            clear(App.renderer);
            switch(event.type){
                case SDL_QUIT: return 1;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RIGHT){
                        // If right most go bottom index
                        if (index == len - 1){
                            index = 0;
                            break;
                        }
                        if (index < len){
                            ++index;
                        }
                    }

                    if (event.key.keysym.sym == SDLK_LEFT){
                        // If left most go to top index
                        if (index == 0){
                            index = len;
                        }
                        if (index > 0){
                            --index;
                        }
                    }
                 break;
            }

            render(App.renderer, &FLAGS[index]);
        }
    
        SDL_RenderPresent(App.renderer);
    }

    printf("Leaving FLAGGRRR!\n");
    destroy(&App);

    return 0;
}