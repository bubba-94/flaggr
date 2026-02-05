#ifndef FLAGGR_H
#define FLAGGR_H

#include <stdint.h>
#include <SDL2/SDL.h>

static const uint16_t WINDOW_WIDTH = 1080;
static const uint16_t WINDOW_HEIGHT = 640;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
}App;

// SET COLORS
typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color;

typedef enum {
    WHITE,
    BLACK,
    RED,
    DARK_RED,
    LIGHT_RED,
    BLUE,
    DARK_BLUE,
    LIGHT_BLUE,
    GREEN,
    DARK_GREEN,
    LIGHT_GREEN,
    YELLOW,
    GOLD,
    DARK_YELLOW,
    ORANGE,
    PURPLE,
    BROWN,
    CYAN
} ColorId;

typedef struct{
    uint16_t w, h;      // Specs of Flag
    uint16_t x, y;      // Cursor of Flag
    size_t amount;      // Amount of colors in Flag
    ColorId *primary;    // Dynamic per flag
    ColorId background;
}Flag;

static const Color TABLE[] = {
    [WHITE]         = { 255, 255, 255 },
    [BLACK]         = {   0,   0,   0 },
    [RED]           = { 206,  17,  38 },
    [DARK_RED]      = { 170,   0,   0 },
    [LIGHT_RED]     = { 239,  51,  64 },
    [BLUE]          = {   0, 106, 167 },
    [DARK_BLUE]     = {   0,  40, 104 },
    [LIGHT_BLUE]    = {  65, 143, 222 },
    [GREEN]         = {   0, 122,  61 },
    [DARK_GREEN]    = {   0, 100,   0 },
    [LIGHT_GREEN]   = {  60, 179, 113 },
    [YELLOW]        = { 254, 204,   0 },
    [GOLD]          = { 255, 215,   0 },
    [DARK_YELLOW]   = { 218, 165,  32 },
    [ORANGE]        = { 255, 140,   0 }, 
    [PURPLE]        = { 102,  45, 145 },
    [BROWN]         = { 139,  69,  19 }, 
    [CYAN]          = {   0, 188, 212 }
};

// Logic
int init(App *app, const char *title, int w, int h);
void destroy(App *app);
void set_flag_color(SDL_Renderer *r, ColorId id);
void set_bg_color(SDL_Renderer *r, ColorId id);

// Flag prints
void sweden(SDL_Renderer *renderer);
void finland(SDL_Renderer *renderer);


#endif