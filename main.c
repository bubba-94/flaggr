#include "flaggr.h"
#include <stdio.h>
#include <cjson/cJSON.h>

/*
    EXTENSIONS

    1. Store flag definitions in a file (JSON, CSV, or custom format) and load at runtime.
    2. Instead of fixed width/height, compute flag sizes based on window dimensions.
    3. Add a small UI to select flags instead of just arrow keys.
    4. Make flags fade in/out, “wave,” or highlight a cross dynamically.
*/

int main(int argc, char *argv[]) {
    
    if(argc < 2){
        printf("No config file provided\n");
        return -1; 
    }

    App App = {0};
    static FlagSpec flags[MAX_FLAGS];
    int running = 1;

    // Read file 
    int count = read_config(argv[1], flags);
    // Abort if no flags read
    if (count < 1) return 1;


    /*
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
        */

    size_t len = count;
    if (!init(&App, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT)) return 1;
    
    size_t index = 0;

    while (running){

        clear(App.renderer);
        // Register event
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RIGHT){
                        if (index == len - 1)
                            index = 0;
                        else
                            ++index;
                    }

                    if (event.key.keysym.sym == SDLK_LEFT){
                        if (index == 0)
                            index = len - 1;
                        else
                            --index;
                    }
            break;
            }
        }

        render(App.renderer, &flags[index]);
    }

    printf("Leaving FLAGGRRR!\n");
    destroy(&App);

    return 0;
}