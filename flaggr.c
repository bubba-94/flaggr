#include "flaggr.h"

static TextLayout text = {
    .w = 0,
    .x = 0,
    .HEIGHT = 150,
    .Y_POS = (WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 2)
};

static const int CHAR_WIDTH = 50;
static const int CHAR_PADDING = 10;

void Sweden(SDL_Renderer *renderer){
    clear(renderer);
    ColorId colors[] = {BLUE,YELLOW};

    Flag *Sweden = flag("Sweden", colors, 2);
    if(!Sweden) return;

    render_title(Sweden, renderer);

    draw_nordic(Sweden, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Sweden);
}

void Norway(SDL_Renderer *renderer){
    clear(renderer);
    ColorId colors[] = {RED, WHITE, BLUE};

    Flag *Norway = flag("Norway", colors, 3);
    if(!Norway) return;

    render_title(Norway, renderer);

    draw_nordic(Norway, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Norway);
}

void Iceland(SDL_Renderer *renderer){
    clear(renderer);
    ColorId colors[] = {BLUE, WHITE, RED};

    Flag *Iceland = flag("Iceland", colors, 3);
    if(!Iceland) return;

    render_title(Iceland, renderer);

    draw_nordic(Iceland, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Iceland);
}

void FaroeIslands(SDL_Renderer *renderer){
    clear(renderer);
    ColorId colors[] = {WHITE, BLUE, RED};

    Flag *FaroeIslands = flag("Faroe Islands", colors, 3);
    if(!FaroeIslands) return;

    render_title(FaroeIslands, renderer);

    draw_nordic(FaroeIslands, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(FaroeIslands);
}

void Denmark(SDL_Renderer *renderer){
    clear(renderer);
    ColorId colors[] = {RED, WHITE};

    Flag *Denmark = flag("Denmark", colors, 2);
    if(!Denmark) return;

    render_title(Denmark, renderer);

    draw_nordic(Denmark, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Denmark);
}

void Finland(SDL_Renderer *renderer){
    clear(renderer);
    ColorId colors[] = {WHITE,BLUE};

    Flag *Finland = flag("Finland", colors, 2);
    if(!Finland) return;

    render_title(Finland, renderer);

    draw_nordic(Finland, renderer);

    SDL_RenderPresent(renderer);

    destroy_flag(Finland);

}

void render_title(Flag *f, SDL_Renderer *renderer){

    TTF_Font *font = TTF_OpenFont("Lato-Light.ttf", 400);

    if (!font){
        printf("Font error: %s\n", SDL_GetError());
        TTF_CloseFont(font);
    }

      // Create surface with rendered text
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, f->title, textColor);

    if (!textSurface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
    }

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (!texture){
        printf("Failed to create text texture: %s\n", SDL_GetError());
    }

    text.w = get_text_width(f->title);
    text.x = get_text_x(f->title);

    // Render text
    SDL_Rect textRect = {text.x, text.Y_POS, text.w, text.HEIGHT};

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
  
}

uint16_t get_text_x(const char *title){
    int textWidth = get_text_width(title);
    return (WINDOW_WIDTH - textWidth) / 2;
}

uint16_t get_text_width(const char *title){
    int len = strlen(title);

    if (len == 0) return 0;

    return (len * CHAR_WIDTH) + ((len - 1) * CHAR_PADDING);
}

void clear(SDL_Renderer *r){
    SDL_SetRenderDrawColor(r, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(r);
}

void draw_nordic(const Flag *f, SDL_Renderer *r){
    const int crossThickness = f->h / 5;
    const int verticalX = f->x + f->w * 5 / 16;
    const int horizontalY = f->y + f->h / 2 - crossThickness / 2;
    

    // Clear screen greyis)
    set_color(r, f->background);

    // Color of flag bg
    set_color(r, f->primary[0]);
    SDL_Rect bg = { f->x, f->y, f->w, f->h };
    SDL_RenderFillRect(r, &bg);

    // Vertical bar
    set_color(r, f->primary[1]);
    SDL_Rect vbar = {
        verticalX,
        f->y,
        crossThickness,
        f->h
    };
    SDL_RenderFillRect(r, &vbar);

    // Horizontal bar
    SDL_Rect hbar = {
        f->x,
        horizontalY,
        f->w,
        crossThickness
    };
    
    SDL_RenderFillRect(r, &hbar);
    // Third cross in the middle
    if (f->amount > 2){
        set_color(r , f->primary[2]);
        const int thicknessM = crossThickness / 2;
        const int verticalMX = verticalX + thicknessM / 2 - 1 ;
        const int horizontalMY = horizontalY + thicknessM / 2 - 1;
        
        // Vertical
        SDL_Rect mxbar = {
            verticalMX,
            f->y,
            thicknessM,
            f->h
        };
        SDL_RenderFillRect(r, &mxbar);

        SDL_Rect mybar = {
            f->x,
            horizontalMY,
            f->w,
            thicknessM
        };
        SDL_RenderFillRect(r, &mybar);
    }

    
}

Flag* flag(const char* title, ColorId* c, int n){
    Flag *f = malloc(sizeof *f);
    if (!f) return NULL;

    f->title = title;
    f->h = 300;
    f->w = f->h * 2; 
    f->x = (WINDOW_WIDTH  - f->w) / 2;
    f->y = (WINDOW_HEIGHT - f->h) / 2;
    f->amount = n;

    f->primary = malloc(sizeof(ColorId) * n);
    if (!f->primary) {
        free(f);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        f->primary[i] = c[i];

    f->background = BLACK;
    return f;
}

void destroy_flag(Flag *f){
    if(!f) return;

    // Free colors first
    free(f->primary);
    free(f);
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
