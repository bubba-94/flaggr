#include "flaggr.h"

void render_title(const char* title, SDL_Renderer *renderer){

    const TextLayout text = {
        .w = get_text_width(title),
        .x = get_text_x(title),
        .HEIGHT = 150,
        .Y_POS = (WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 2)
    };

    TTF_Font *font = TTF_OpenFont("Lato-Light.ttf", 400);

    if (!font){
        printf("Font error: %s\n", SDL_GetError());
        TTF_CloseFont(font);
    }

      // Create surface with rendered text
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, title, textColor);

    if (!textSurface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
    }

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (!texture){
        printf("Failed to create text texture: %s\n", SDL_GetError());
    }

    // Render text
    SDL_Rect textRect = {text.x, text.Y_POS, text.w, text.HEIGHT};

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}

uint16_t get_text_x(const char *title){
    int textWidth = get_text_width(title);
    return (WINDOW_WIDTH - textWidth) / 2;
}

uint16_t get_text_width(const char *title){
    const int CHAR_WIDTH = 50;
    const int CHAR_PADDING = 10;
    int len = strlen(title);

    if (len == 0) return 0;

    return (len * CHAR_WIDTH) + ((len - 1) * CHAR_PADDING);
}

void clear(SDL_Renderer *r){
    SDL_SetRenderDrawColor(r, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(r);
}

void create_nordic_flag(const FlagSpec *f, SDL_Renderer *r){

    const int H = 300;
    const int W = H * 2;
    const int X = (WINDOW_WIDTH  - W) / 2;
    const int Y = (WINDOW_HEIGHT - H) / 2;
    const int crossThickness = H / 5;
    const int verticalX = X + W * 5 / 16;
    const int horizontalY = Y + H / 2 - crossThickness / 2;

    // Color of flag bg
    set_color(r, f->colors[0]);
    SDL_Rect bg = { X, Y, W, H };
    SDL_RenderFillRect(r, &bg);

    // Vertical bar
    set_color(r, f->colors[1]);
    SDL_Rect vbar = {
        verticalX,
        Y,
        crossThickness,
        H,
    };
    SDL_RenderFillRect(r, &vbar);

    // Horizontal bar
    SDL_Rect hbar = {
        X,
        horizontalY,
        W,
        crossThickness
    };
    
    SDL_RenderFillRect(r, &hbar);
    // Third cross in the middle
    if (f->amount > 2){
        set_color(r , f->colors[2]);
        const int thicknessM = crossThickness / 2;
        const int verticalMX = verticalX + thicknessM / 2 - 1 ;
        const int horizontalMY = horizontalY + thicknessM / 2 - 1;
        
        // Vertical
        SDL_Rect mxbar = {
            verticalMX,
            Y,
            thicknessM,
            H
        };
        SDL_RenderFillRect(r, &mxbar);

        SDL_Rect mybar = {
            X,
            horizontalMY,
            W,
            thicknessM
        };
        SDL_RenderFillRect(r, &mybar);
    }

    
}

void set_color(SDL_Renderer *r, ColorId id)
{
    Color c = TABLE[id];
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
}

int init(App *app, const char *title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() < 0){
        printf("SDL_TTF error: %s\n", SDL_GetError());
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
        destroy(app);
        return 0;
    }

    app->renderer = SDL_CreateRenderer(
        app->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!app->renderer) {
        printf("Renderer error: %s\n", SDL_GetError());
        destroy(app);
        return 0;
    }

    return 1;
}

void destroy(App *app) {
    if (app->renderer)
        SDL_DestroyRenderer(app->renderer);

    TTF_Quit();

    if (app->window)
        SDL_DestroyWindow(app->window);

    SDL_Quit();
}
