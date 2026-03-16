#ifndef FLAGGRTYPES_H
#define FLAGGRTYPES_H

// External libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cjson/cJSON.h>

// C standard libraries
#include <stdint.h>
#include <string.h>

#define MAX_COLORS 10
#define MAX_FLAGS 25

static const uint16_t WINDOW_WIDTH = 2000;
static const uint16_t WINDOW_HEIGHT = 1000;
static const uint16_t DELAY_MS = 500;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    
}App;

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color; 

typedef struct{
    uint16_t w;
    uint16_t x;
    const uint16_t HEIGHT;
    const uint16_t Y_POS;
}TextLayout;

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

typedef enum{
    FLAG_NORDIC,
    FLAG_HORIZONTAL,
    FLAG_TRICOLOR,
    FLAG_TRICOLOR_VERTICAL,
    FLAG_VERTICAL,
    FLAG_VERTICAL_STRIPES,
    FLAG_CENTER_CROSS,
    FLAG_CIRCLE
}FlagType;

typedef struct{
    const char* title;
    size_t amount;
    FlagType type;
    ColorId colors[MAX_COLORS];
}FlagSpec;

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

#endif