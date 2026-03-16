#include "flaggr.h"
#include <stdio.h>
#include <cjson/cJSON.h>

/*
    EXTENSIONS
 
    X   1. Store flag definitions in a file (JSON, CSV, or custom format) and load at runtime.
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

    // Read file config
    int flag_count = read_config(argv[1], flags);
    
    // Abort if no flags read
    if (flag_count < 1) return 1;

    size_t len = flag_count;
    size_t index = 0;

    // Initilize SDL
    if (!init(&App, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT)) return 1;
    
    // Application
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