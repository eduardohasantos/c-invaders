
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "score.h"
#include "screen.h"

#define HIGHSCORE_COUNT 3
#define HIGHSCORE_FILE "highscore.txt"

static int g_score = 0;
static Highscore g_highscores[HIGHSCORE_COUNT];

void score_init(void) {
    g_score = 0;
    // Carrega os recordes no início do jogo
    highscore_load();
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

/* --- Funções de Highscore --- */

void highscore_load(void) {
    FILE* fp = fopen(HIGHSCORE_FILE, "r");
    if (!fp) {
        // Se o ficheiro não existe, inicializa com valores padrão
        for (int i = 0; i < HIGHSCORE_COUNT; ++i) {
            strcpy(g_highscores[i].name, "N/A");
            g_highscores[i].score = 0;
        }
        return;
    }

    for (int i = 0; i < HIGHSCORE_COUNT; ++i) {
        // Ignora o resto da linha se a leitura falhar
        if (fscanf(fp, "%3s %d %d\n", g_highscores[i].name, &g_highscores[i].score, &g_highscores[i].round) != 3) {
             strcpy(g_highscores[i].name, "N/A");
             g_highscores[i].score = 0;
             g_highscores[i].round = 0;
        }
    }
    fclose(fp);
}

void highscore_save(void) {
    FILE* fp = fopen(HIGHSCORE_FILE, "w");
    if (!fp) return; // Não foi possível abrir para escrita

    for (int i = 0; i < HIGHSCORE_COUNT; ++i) {
        fprintf(fp, "%s %d %d\n", g_highscores[i].name, g_highscores[i].score, g_highscores[i].round);
    }
    fclose(fp);
}

int highscore_check_and_add(const char* name, int score, int round) {
    int new_highscore_pos = -1;
    for (int i = 0; i < HIGHSCORE_COUNT; ++i) {
        if (score > g_highscores[i].score) {
            new_highscore_pos = i;
            break;
        }
    }

    if (new_highscore_pos != -1) {
        // Move os scores antigos para baixo
        for (int i = HIGHSCORE_COUNT - 1; i > new_highscore_pos; --i) {
            g_highscores[i] = g_highscores[i - 1];
        }
        // Insere o novo score
        strcpy(g_highscores[new_highscore_pos].name, name);
        g_highscores[new_highscore_pos].score = score;
        g_highscores[new_highscore_pos].round = round;
        highscore_save();
    }
    return new_highscore_pos;
}

void highscore_draw(int y_start) {
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(30, y_start);
    printf("MELHORES PONTUAÇÕES");
    for (int i = 0; i < HIGHSCORE_COUNT; ++i) {
        screenGotoxy(32, y_start + 2 + i);
        printf("%d. %s %d (Ronda %d)", i + 1, g_highscores[i].name, g_highscores[i].score, g_highscores[i].round);
    }
}
