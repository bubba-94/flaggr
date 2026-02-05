#include "flaggr.h"

int init(App *app, const char *title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 0;
    }

    app->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_SHOWN
    );

    if (!app->window) {
        printf("Window error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    app->renderer = SDL_CreateRenderer(
        app->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!app->renderer) {
        printf("Renderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void destroy(App *app) {
    if (app->renderer)
        SDL_DestroyRenderer(app->renderer);

    if (app->window)
        SDL_DestroyWindow(app->window);

    SDL_Quit();
}

void set_flag_color(SDL_Renderer *r, ColorId id)
{
    Color c = TABLE[id];
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
}
void set_bg_color(SDL_Renderer *r, ColorId id)
{
    Color c = TABLE[id];
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
}

void sweden(SDL_Renderer *renderer) {

    Flag sweden;
    sweden.h = 300;
    sweden.w = sweden.h * (10 / 5);
    sweden.x = (WINDOW_WIDTH / 2) - (sweden.w / 2);
    sweden.y = (WINDOW_HEIGHT / 2) - (sweden.h / 2);
    sweden.amount = 2;
    sweden.primary = malloc(sizeof(ColorId) * sweden.amount);
    sweden.primary[0] = BLUE;
    sweden.primary[1] = YELLOW;
    sweden.background = BLACK;

    const int crossThickness = sweden.h / 5;
    const int verticalX = sweden.x + sweden.w * 5 / 16;
    const int horizontalY = sweden.y + sweden.h / 2 - crossThickness / 2;

    // Clear screen greyis)
    set_bg_color(renderer, sweden.background);
    // Blue background 
    set_flag_color(renderer, sweden.primary[0]);
    SDL_Rect bg = { sweden.x, sweden.y, sweden.w, sweden.h };
    SDL_RenderFillRect(renderer, &bg);

    // Yellow vertical bar
    set_flag_color(renderer, sweden.primary[1]);
    SDL_Rect vbar = {
        verticalX,
        sweden.y,
        crossThickness,
        sweden.h
    };
    SDL_RenderFillRect(renderer, &vbar);

    free(sweden.primary);

    // Yellow horizontal bar
    SDL_Rect hbar = {
        sweden.x,
        horizontalY,
        sweden.w,
        crossThickness
    };
    SDL_RenderFillRect(renderer, &hbar);

    SDL_RenderPresent(renderer);
}

void finland(SDL_Renderer *renderer){
    
    Flag finland;
    finland.h = 300;
    finland.w = finland.h * (10 / 5);
    finland.x = (WINDOW_WIDTH / 2) - (finland.w / 2);
    finland.y = (WINDOW_HEIGHT / 2) - (finland.h / 2);
    finland.amount = 2;
    finland.primary = malloc(sizeof(ColorId) * finland.amount);
    finland.primary[0] = WHITE;
    finland.primary[1] = BLUE;
    finland.background = BLACK;

    const int crossThickness = finland.h / 5;
    const int verticalX = finland.x + finland.w * 5 / 16;
    const int horizontalY = finland.y + finland.h / 2 - crossThickness / 2;

    // Clear screen greyis)
    set_bg_color(renderer, finland.background);
    // Blue background 
    set_flag_color(renderer, finland.primary[0]);
    SDL_Rect bg = { finland.x, finland.y, finland.w, finland.h };
    SDL_RenderFillRect(renderer, &bg);

    // Yellow vertical bar
    set_flag_color(renderer, finland.primary[1]);
    SDL_Rect vbar = {
        verticalX,
        finland.y,
        crossThickness,
        finland.h
    };
    SDL_RenderFillRect(renderer, &vbar);

    free(finland.primary);

    // Yellow horizontal bar
    SDL_Rect hbar = {
        finland.x,
        horizontalY,
        finland.w,
        crossThickness
    };
    SDL_RenderFillRect(renderer, &hbar);

    SDL_RenderPresent(renderer);
}
