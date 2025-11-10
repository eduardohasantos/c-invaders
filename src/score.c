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

/* Desenha o score imediatamente abaixo da área do jogo (SCRENDY + 1).
   Chame esta função depois de screenUpdate() para evitar que seja sobrescrita. */
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

    int desired_row = SCRENDY + 1; /* linha logo abaixo da área do jogo */
    int row;
    if (term_rows > 0) {
        if (desired_row > 0 && desired_row <= term_rows) row = desired_row;
        else row = term_rows;
    } else {
        row = desired_row > 0 ? desired_row : 1;
    }

    int width = (term_cols > 0) ? term_cols : len;

    /* salva cursor, move para linha/col 1, escreve e restaura cursor */
    printf("\x1b[s");                    /* save cursor */
    printf("\x1b[%d;1H", row);           /* move to desired row, col 1 */
    printf("%-*s", width, buf);          /* write and clear rest of line */
    printf("\x1b[u");                    /* restore cursor */
    fflush(stdout);
}