#ifndef FLAGGR_H
#define FLAGGR_H

#include "flaggrtypes.h"

// Actual flags

void Sweden(SDL_Renderer *renderer);
void Norway(SDL_Renderer *renderer);
void Denmark(SDL_Renderer *renderer);
void Finland(SDL_Renderer *renderer);
void Iceland(SDL_Renderer *renderer);
void FaroeIslands(SDL_Renderer *renderer);

// General flag outlines

void draw_nordic(const Flag* f, SDL_Renderer *r);

// Logic

Flag* flag(const char* title, ColorId* c, int n);
void destroy_flag(Flag *f);

// Coloring

void set_color(SDL_Renderer *r, ColorId id);
void render_title(Flag *f, SDL_Renderer *renderer);

// Adjustments

int get_text_width(const char *title){}

// Application

int init(App *app, const char *title, int w, int h);
void destroy(App *app);

#endif