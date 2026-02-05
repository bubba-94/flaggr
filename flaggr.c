#include "flaggr.h"
void Sweden(SDL_Renderer *renderer){
    ColorId colors[] = {BLUE,YELLOW};

    Flag *Sweden = flag(colors, 2);
    if(!Sweden) return;

    draw_nordic(Sweden, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Sweden);
}

void Norway(SDL_Renderer *renderer){
    ColorId colors[] = {RED, WHITE, BLUE};

    Flag *Norway = flag(colors, 3);
    if(!Norway) return;

    draw_nordic(Norway, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Norway);
}

void Iceland(SDL_Renderer *renderer){
    ColorId colors[] = {BLUE, WHITE, RED};

    Flag *Iceland = flag(colors, 3);
    if(!Iceland) return;

    draw_nordic(Iceland, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Iceland);
}

void FaroeIslands(SDL_Renderer *renderer){
    ColorId colors[] = {WHITE, BLUE, RED};

    Flag *FaroeIslands = flag(colors, 3);
    if(!FaroeIslands) return;

    draw_nordic(FaroeIslands, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(FaroeIslands);
}

void Denmark(SDL_Renderer *renderer){
    ColorId colors[] = {RED, WHITE};

    Flag *Denmark = flag(colors, 2);
    if(!Denmark) return;

    draw_nordic(Denmark, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Denmark);
}

void Finland(SDL_Renderer *renderer){
    
    ColorId colors[] = {WHITE,BLUE};

    Flag *Finland = flag(colors, 2);
    if(!Finland) return;

    draw_nordic(Finland, renderer);
    
    SDL_RenderPresent(renderer);

    destroy_flag(Finland);
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

Flag* flag(ColorId* c, int n){
    Flag *f = malloc(sizeof *f);
    if (!f) return NULL;

    f->h = 300;
    f->w = f->h * 2; // see next section
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
