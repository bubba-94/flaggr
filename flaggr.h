#ifndef FLAGGR_H
#define FLAGGR_H

#include "flaggrtypes.h"

void render(SDL_Renderer* r, const FlagSpec* f);

// General flag outlines

void create_nordic_flag(const FlagSpec* f, SDL_Renderer *r);
void create_horizontal_flag(const FlagSpec *f, SDL_Renderer *r);

// Logic

void render_title(const char* title, SDL_Renderer *renderer);
void set_color(SDL_Renderer *r, ColorId id);
void clear(SDL_Renderer *r);

// Adjustments

uint16_t get_text_width(const char *title);
uint16_t get_text_x(const char *title);

// Application

int init(App *app, const char *title, int w, int h);
void destroy(App *app);

#endif