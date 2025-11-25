#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "score.h"
#include "screen.h"

static int g_score = 0;

void score_init(void) {
    g_score = 0;
}

void score_reset(void) {
    g_score = 0;
}

void score_add(int points) {
    g_score += points;
    if (g_score < 0) g_score = 0;
}

int score_get(void) {
    return g_score;
}

void score_draw(void) {
    char buf[64];
    int len = snprintf(buf, sizeof(buf), "Score: %d", g_score);
    if (len <= 0) return;

    struct winsize w;
    int term_rows = 0;
    int term_cols = 0;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        term_rows = (int)w.ws_row;
        term_cols = (int)w.ws_col;
    }

    int row = 3;
    int col = 4;

    /* salva cursor, move para linha/col especificadas, escreve e restaura cursor */
    printf("\x1b[s");                    /* save cursor */
    printf("\x1b[%d;%dH", row, col);     /* move to row;col */
    printf("%s", buf);                   /* write */
    printf("\x1b[u");                    /* restore cursor */
    fflush(stdout);
}
