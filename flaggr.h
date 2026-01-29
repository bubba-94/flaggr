#ifndef FLAGGR_H
#define FLAGGR_H

#include <stdio.h>

#define COLS 120
#define ROWS 40

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

// ASCII colors
#define RESET      "\033[0m"
#define GREY       "\033[48;5;102m"
#define BLUE       "\033[48;5;20m" 
#define WHITE      "\033[48;5;255m"
#define RED        "\033[48;5;196m"
#define GREEN      "\033[48;5;82m"
#define YELLOW     "\033[48;5;226m"
#define ORANGE     "\033[48;5;208m"
#define PURPLE     "\033[48;5;129m"
#define CYAN       "\033[48;5;51m"

// Enums for ASCII colors
typedef enum {
    DRAW_GREEN,
    DRAW_WHITE,
    DRAW_RED,
    DRAW_BLACK,
    DRAW_YELLOW,
    DRAW_BLUE,
    DRAW_ORANGE,
    DRAW_PURPLE,
    DRAW_CYAN,
    DRAW_GREY
} Color;

typedef struct {
    int x;
    int y;
    int z;
} Border; 

// Flag structure
typedef struct {
    Color pixels[ROWS][COLS];
} FlagBuffer;

void render(const FlagBuffer *flag);

// Different flags
void germany(FlagBuffer *flag);
void japan(FlagBuffer *flag);
void italy(FlagBuffer *flag);
void france(FlagBuffer *flag);

#endif