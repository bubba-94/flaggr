#include "flaggr.h"
#include <stdio.h>

int main(void) {
    App App = {0};
    
    SDL_Event event;

    // Add flags to this array
    static const FlagSpec FLAGS[] = {
        {"Sweden"       , 2, FLAG_NORDIC, {BLUE, YELLOW}},
        {"Norway"       , 3, FLAG_NORDIC, {RED, WHITE, BLUE}},
        {"Denmark"      , 2, FLAG_NORDIC, {RED, WHITE}},
        {"Finland"      , 2, FLAG_NORDIC, {WHITE, BLUE}},
        {"Iceland"      , 3, FLAG_NORDIC, {BLUE, WHITE, RED}},
        {"Faroe Islands", 3, FLAG_NORDIC, {WHITE, RED, BLUE}},
        {"Estonia"      , 3, FLAG_HORIZONTAL, {BLUE, BLACK, WHITE}},
        {"Lithuania"    , 3, FLAG_HORIZONTAL, {DARK_YELLOW, DARK_GREEN, DARK_RED}},
        {"Germany"      , 3, FLAG_HORIZONTAL, {BLACK, RED, YELLOW}},
        {"Russia"       , 3, FLAG_HORIZONTAL, {WHITE, BLUE, RED}},
        {"Luxembourg"   , 3, FLAG_HORIZONTAL, {RED, WHITE, LIGHT_BLUE}},
        {"Poland"       , 2, FLAG_HORIZONTAL, {RED, WHITE}},
        {"Hungary"      , 3, FLAG_HORIZONTAL, {RED, WHITE, DARK_GREEN}},
    };

    size_t len = sizeof(FLAGS) / sizeof(FLAGS[0]);
    
    if (!init(&App, "flaggr", WINDOW_WIDTH, WINDOW_HEIGHT)) return 1;
    
    for(size_t index = 0; index < len; ++index){
        clear(App.renderer);
        render(App.renderer, &FLAGS[index]);
        SDL_RenderPresent(App.renderer);
        SDL_Delay(DELAY_MS);
    }

    printf("Bye bye!\n");
    destroy(&App);

    return 0;
}