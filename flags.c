#include "flaggr.h"

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
