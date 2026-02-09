#include "flaggr.h"
#include <stdio.h>

int main(void) {
    App App = {0};
    
    SDL_Event event;
    
    void (*flag_arr[])(SDL_Renderer* renderer) = {
        Sweden, Norway, Denmark,
        Finland, Iceland, FaroeIslands
    };

    size_t len = sizeof(flag_arr);
    size_t index = 0;
    
    if (!init(&App, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT))
        return 1;

    while (index <= len - 1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type){
                case SDL_QUIT:
                    index = len;
                break;
            }
        }

        flag_arr[index](App.renderer);

        SDL_Delay(DELAY_MS);

        ++index;
    }

    printf("Bye bye!\n");
    destroy(&App);

    return 0;
}