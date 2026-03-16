#include "flaggr.h"

// Render result
void render(SDL_Renderer* renderer, const FlagSpec* f){
    switch (f->type){
        case FLAG_NORDIC:               create_nordic_flag(f, renderer); break;
        case FLAG_HORIZONTAL:           create_horizontal_flag(f, renderer); break;
        case FLAG_TRICOLOR: break;
        case FLAG_TRICOLOR_VERTICAL: break;
        case FLAG_VERTICAL: break;
        case FLAG_VERTICAL_STRIPES: break;
        case FLAG_CENTER_CROSS: break;
        case FLAG_CIRCLE: break;
    }
    SDL_RenderPresent(renderer);
}

void create_horizontal_flag(const FlagSpec *f, SDL_Renderer *r){
    render_title(f->title, r);

    SDL_Rect bars[f->amount];

    const int H = WINDOW_HEIGHT / 2;
    const int W = WINDOW_WIDTH / 2;
    const int X = (WINDOW_WIDTH  - W) / 2;
    const int Y = (WINDOW_HEIGHT - H) / 2;
    
    const int HORIZONTAL_THICKNESS = H / f->amount;

    for (size_t i = 0; i < f->amount; i++){
        set_color(r, f->colors[i]);

        // Fill current flag.
        bars[i].x = X;
        bars[i].y = Y + HORIZONTAL_THICKNESS * i;
        bars[i].w = W;
        bars[i].h = HORIZONTAL_THICKNESS;

        SDL_RenderFillRect(r, &bars[i]);
    }
}

void create_nordic_flag(const FlagSpec *f, SDL_Renderer *r){

    render_title(f->title, r);

    const int H = WINDOW_HEIGHT / 2;
    const int W = WINDOW_WIDTH / 2;
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
    const int CHAR_PADDING = 20;
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

    TTF_CloseFont(font);

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

int read_config(const char *file, FlagSpec *flags) {

    FILE *fd = fopen(file, "r");
    if (!fd) {
        printf("Error opening %s\n", file);
        return 0;
    }

    char buffer[10000];
    size_t len = fread(buffer, 1, sizeof(buffer)-1, fd);
    buffer[len] = '\0';
    fclose(fd);

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        printf("Parse error\n");
        return 0;
    }

    if (!cJSON_IsArray(json)) {
        printf("Root should be array\n");
        cJSON_Delete(json);
        return 0;
    }

    int count = cJSON_GetArraySize(json);
    int flagsRead = 0;

    for (int i = 0; i < count; i++) {

        cJSON *item = cJSON_GetArrayItem(json, i);

        cJSON *country = cJSON_GetObjectItemCaseSensitive(item, "country");
        cJSON *amount  = cJSON_GetObjectItemCaseSensitive(item, "amount");
        cJSON *type    = cJSON_GetObjectItemCaseSensitive(item, "type");
        cJSON *colors  = cJSON_GetObjectItemCaseSensitive(item, "colors");

        if (cJSON_IsString(country))
            flags[i].title = strdup(country->valuestring);

        if (cJSON_IsNumber(amount))
            flags[i].amount = amount->valueint;

        if (cJSON_IsString(type))
            flags[i].type = typestrToEnum(type->valuestring);

        if (cJSON_IsArray(colors)) {

            size_t colorLen = cJSON_GetArraySize(colors);

            for (size_t j = 0; j < colorLen && j < 10; j++) {

                cJSON *color = cJSON_GetArrayItem(colors, j);

                if (cJSON_IsString(color))
                    flags[i].colors[j] = colorstrToEnum(color->valuestring);
            }
        }

        flagsRead++;
    }

    cJSON_Delete(json);
    return flagsRead;
}


// Map type string to enum
FlagType typestrToEnum(const char* str) {

    switch(str[0]) {

        case 'n':
            if(strcmp(str,"nordic")==0) return FLAG_NORDIC;
            break;

        case 'h':
            if(strcmp(str,"horizontal")==0) return FLAG_HORIZONTAL;
            break;

        case 'v':
            if(strcmp(str,"vertical")==0) return FLAG_VERTICAL;
            if(strcmp(str,"vertical_stripes")==0) return FLAG_VERTICAL_STRIPES;
            break;

        case 't':
            if(strcmp(str,"tricolor")==0) return FLAG_TRICOLOR;
            if(strcmp(str,"tricolorvert")==0) return FLAG_TRICOLOR_VERTICAL;
            break;

    }
        return -1; // Error
}

// Map color string to enum
ColorId colorstrToEnum(const char* str) {

    switch(str[0]) {

        case 'w':
            if(strcmp(str,"white")==0) return WHITE;
            break;

        case 'b':
            if(strcmp(str,"black")==0) return BLACK;
            if(strcmp(str,"blue")==0) return BLUE;
            if(strcmp(str,"brown")==0) return BROWN;
            break;

        case 'r':
            if(strcmp(str,"red")==0) return RED;
            break;

        case 'd':
            if(strcmp(str,"dark_red")==0) return DARK_RED;
            if(strcmp(str,"dark_blue")==0) return DARK_BLUE;
            if(strcmp(str,"dark_green")==0) return DARK_GREEN;
            if(strcmp(str,"dark_yellow")==0) return DARK_YELLOW;
            break;

        case 'l':
            if(strcmp(str,"light_red")==0) return LIGHT_RED;
            if(strcmp(str,"light_blue")==0) return LIGHT_BLUE;
            if(strcmp(str,"light_green")==0) return LIGHT_GREEN;
            break;

        case 'g':
            if(strcmp(str,"green")==0) return GREEN;
            if(strcmp(str,"gold")==0) return GOLD;
            break;

        case 'y':
            if(strcmp(str,"yellow")==0) return YELLOW;
            break;

        case 'o':
            if(strcmp(str,"orange")==0) return ORANGE;
            break;

        case 'p':
            if(strcmp(str,"purple")==0) return PURPLE;
            break;

        case 'c':
            if(strcmp(str,"cyan")==0) return CYAN;
            break;
    }

    return -1;
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