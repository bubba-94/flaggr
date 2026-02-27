#include "flaggr.h"
#include <stdio.h>

int main(void) {
    App App = {0};
    
    SDL_Event event;

    size_t len = sizeof(FLAGS) / sizeof(FLAGS[0]);
    
    if (!init(&App, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT)) return 1;
    
    for(size_t index = 0; index < len; ++index){
        render(App.renderer, &FLAGS[index]);
        SDL_Delay(DELAY_MS);
    }

    printf("Bye bye!\n");
    destroy(&App);

    return 0;
}