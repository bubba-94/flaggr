#include "flaggr.h"

void render(const FlagBuffer *flag){

    for (int r = 0; r < ROWS; r++) {
        printf("%s ", GREY);
        for (int c = 0; c < COLS; c++) {
            switch (flag->pixels[r][c]) {
                case DRAW_BLACK:    printf("%s ", RESET); break;
                case DRAW_BLUE:     printf("%s ", BLUE); break;
                case DRAW_WHITE:    printf("%s ", WHITE); break;
                case DRAW_RED:      printf("%s ", RED); break;
                case DRAW_GREEN:    printf("%s ", GREEN); break;
                case DRAW_YELLOW:   printf("%s ", YELLOW); break;
                case DRAW_ORANGE:   printf("%s ", ORANGE); break;
                case DRAW_PURPLE:   printf("%s ", PURPLE); break;
                case DRAW_CYAN:     printf("%s ", CYAN); break;
                case DRAW_GREY:     printf("%s ", GREY); break;
            }
        }
        printf("%s ", GREY);
        printf("%s\n", RESET);
    }

    for (int i = 0; i <= COLS + 1; i++){
        printf("%s ", GREY);
    }
    printf("%s", RESET);
    printf("\n");
}

void germany(FlagBuffer *flag){

    // Horizontal
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
            if (r < ROWS / 3)
                flag->pixels[r][c] = DRAW_BLACK;
            else if (r < (2 * ROWS) / 3)
                flag->pixels[r][c] = DRAW_RED;
            else
                flag->pixels[r][c] = DRAW_YELLOW;
        }
    }
}

void japan(FlagBuffer *flag){
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            // Red circle
            if ((r >= 15 && r <= 25) && (c > 48 && c < 72)){
                flag->pixels[r][c] = DRAW_RED;
            }
            else flag->pixels[r][c] = DRAW_WHITE;
        }
    }
}

void italy(FlagBuffer *flag){

    // Vertical
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (c < COLS / 3) {
                flag->pixels[r][c] = DRAW_GREEN;
            } else if (c < (2 * COLS) / 3) {
                flag->pixels[r][c] = DRAW_WHITE;
            } else {
                flag->pixels[r][c] = DRAW_RED;
            }
        }
    }
}

void france(FlagBuffer *flag){
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (c < COLS / 3) {
                flag->pixels[r][c] = DRAW_BLUE;
            } else if (c < (2 * COLS) / 3) {
                flag->pixels[r][c] = DRAW_WHITE;
            } else {
                flag->pixels[r][c] = DRAW_RED;
            }
        }
    }
}