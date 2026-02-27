#include "flaggr.h"

// Add flags to this array
static const FlagSpec FLAGS[] = {
    {"Sweden"       , 2, FLAG_NORDIC, {BLUE, YELLOW}},
    {"Norway"       , 3, FLAG_NORDIC, {RED, WHITE, BLUE}},
    {"Denmark"      , 2, FLAG_NORDIC, {RED, WHITE}},
    {"Finland"      , 2, FLAG_NORDIC, {WHITE, BLUE}},
    {"Iceland"      , 3, FLAG_NORDIC, {BLUE, WHITE, RED}},
    {"Faroe Islands", 3, FLAG_NORDIC, {WHITE, RED, BLUE}},
    {"Germany"      , 3, FLAG_HORIZONTAL, {BLACK, RED, YELLOW}}
};

// Render result
void render(SDL_Renderer* renderer, const FlagSpec* f){
    switch (f->type){
        case FLAG_NORDIC: create_nordic_flag(f, renderer); break;
        case FLAG_HORIZONTAL: create_horizontal_flag(f, renderer); break;
        case FLAG_TRICOLOR_VERTICAL: break;
        case FLAG_CENTER_CROSS: break;
        case FLAG_CIRCLE: break;
    }

    // Present results
    SDL_RenderPresent(renderer);
}

void create_horizontal_flag(const FlagSpec *f, SDL_Renderer *r){
    render_title(f->title, r);

    const int H = 300;
    const int W = H * 2;
    const int X = (WINDOW_WIDTH  - W) / 2;
    const int Y = (WINDOW_HEIGHT - H) / 2;

    
    // Color of flag bg
    set_color(r, f->colors[0]);
    SDL_Rect background = { X, Y, W, H };
    SDL_RenderFillRect(r, &background);
    
    if (f->amount < 3){

        const int HORIZONTAL_THICKNESS = H / 2;
        set_color(r, f->colors[1]);
        SDL_Rect bottom_bar = {
            X,
            Y + 150,
            W,
            HORIZONTAL_THICKNESS,
        };
        SDL_RenderFillRect(r, &bottom_bar);

    }
    else {
        const int HORIZONTAL_THICKNESS = H / 3;
        set_color(r, f->colors[1]);
        SDL_Rect middle_bar = {
            X,
            Y + 100,
            W,
        HORIZONTAL_THICKNESS,
        };
        SDL_RenderFillRect(r, &middle_bar);
    
        set_color(r, f->colors[2]);
        SDL_Rect bottom_bar = {
            X,
            Y + 200,
            W,
            HORIZONTAL_THICKNESS
        };
        SDL_RenderFillRect(r, &bottom_bar);
    }
}

void create_nordic_flag(const FlagSpec *f, SDL_Renderer *r){

    render_title(f->title, r);

    const int H = 300;
    const int W = H * 2;
    const int X = (WINDOW_WIDTH  - W) / 2;
    const int Y = (WINDOW_HEIGHT - H) / 2;
    const int CROSS_THICKNESS = H / 5;
    const int VERTICAL_X = X + W * 5 / 16;
    const int HORIZONTAL_Y = Y + H / 2 - CROSS_THICKNESS / 2;

    // Color of flag bg
    set_color(r, f->colors[0]);
    SDL_Rect bg = { X, Y, W, H };
    SDL_RenderFillRect(r, &bg);

    // Vertical bar
    set_color(r, f->colors[1]);
    SDL_Rect vbar = {
        VERTICAL_X,
        Y,
        CROSS_THICKNESS,
        H,
    };
    SDL_RenderFillRect(r, &vbar);

    // Horizontal bar
    SDL_Rect hbar = {
        X,
        HORIZONTAL_Y,
        W,
        CROSS_THICKNESS
    };
    
    SDL_RenderFillRect(r, &hbar);
    // Third cross in the middle
    if (f->amount > 2){
        set_color(r , f->colors[2]);
        const int THICKNESS_M = CROSS_THICKNESS / 2;
        const int VERTICAL_MX = VERTICAL_X + THICKNESS_M / 2 - 1 ;
        const int HORIZONTAL_MY = HORIZONTAL_Y + THICKNESS_M / 2 - 1;
        
        // Vertical
        SDL_Rect mxbar = {
            VERTICAL_MX,
            Y,
            THICKNESS_M,
            H
        };
        SDL_RenderFillRect(r, &mxbar);

        SDL_Rect mybar = {
            X,
            HORIZONTAL_MY,
            W,
            THICKNESS_M
        };
        SDL_RenderFillRect(r, &mybar);
    }

    
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
    SDL_SetRenderDrawColor(r, 20,20,20, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(r);
}

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
