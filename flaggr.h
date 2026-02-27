#ifndef FLAGGR_H
#define FLAGGR_H

#include "flaggrtypes.h"

static const FlagSpec FLAGS[] = {
        {"Sweden", 2, {BLUE, YELLOW}},
        {"Norway", 3, {RED, WHITE, BLUE}},
        {"Denmark", 2,{RED, WHITE}},
        {"Finland", 2,{WHITE, BLUE}},
        {"Iceland", 3,{BLUE, WHITE, RED}},
        {"Faroe Islands", 3, {WHITE, RED, BLUE}}
    };

void render(SDL_Renderer* r, const FlagSpec* f);

// General flag outlines

void create_nordic_flag(const FlagSpec* f, SDL_Renderer *r);

// Coloring

void set_color(SDL_Renderer *r, ColorId id);
void render_title(const char* title, SDL_Renderer *renderer);
void clear(SDL_Renderer *r);

// Adjustments

uint16_t get_text_width(const char *title);
uint16_t get_text_x(const char *title);

// Application

int init(App *app, const char *title, int w, int h);
void destroy(App *app);

#endif