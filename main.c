#include "flaggr.h"
#include <stdio.h>

int main(void) {
    App app = {0};

    if (!init(&app, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT))
        return 1;

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        sweden(app.renderer);
        SDL_Delay(2000);
        finland(app.renderer);
        SDL_Delay(2000);
    }

    printf("Bye bye!\n");
    destroy(&app);

    return 0;
}