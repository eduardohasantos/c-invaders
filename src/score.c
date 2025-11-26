
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "score.h"
#include "screen.h"

#define HIGHSCORE_DISPLAY_COUNT 3
#define HIGHSCORE_SAVE_COUNT 100
#define HIGHSCORE_FILE "highscore.txt"

typedef struct HighscoreNode {
    Highscore data;
    struct HighscoreNode* next;
} HighscoreNode;

static int g_score = 0;
static HighscoreNode* g_highscore_head = NULL;

void score_init(void) {
    g_score = 0;

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

    

    int row = 3;
    int col = 4;

    printf("\x1b[s");
    printf("\x1b[%d;%dH", row, col);
    printf("%s", buf);
    printf("\x1b[u");
    fflush(stdout);
}



static void highscore_list_clear(void) {
    HighscoreNode* cur = g_highscore_head;
    while (cur) {
        HighscoreNode* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    g_highscore_head = NULL;
}

static void highscore_list_insert_sorted(const char* name, int score, int round) {
    HighscoreNode* node = (HighscoreNode*)malloc(sizeof(HighscoreNode));
    if (!node) return;
    strncpy(node->data.name, name, 3);
    node->data.name[3] = '\0';
    node->data.score = score;
    node->data.round = round;
    node->next = NULL;

    if (!g_highscore_head || score > g_highscore_head->data.score) {
        node->next = g_highscore_head;
        g_highscore_head = node;
    } else {
        HighscoreNode* cur = g_highscore_head;
        while (cur->next && cur->next->data.score >= score) cur = cur->next;
        node->next = cur->next;
        cur->next = node;
    }

    
    int count = 0;
    HighscoreNode* cur = g_highscore_head;
    HighscoreNode* prev = NULL;
    while (cur) {
        count++;
        if (count > HIGHSCORE_SAVE_COUNT) {
            
            if (prev) prev->next = NULL;
            while (cur) {
                HighscoreNode* nxt = cur->next;
                free(cur);
                cur = nxt;
            }
            break;
        }
        prev = cur;
        cur = cur->next;
    }
}

void highscore_load(void) {
    highscore_list_clear();
    FILE* fp = fopen(HIGHSCORE_FILE, "r");
    if (!fp) {
        
        highscore_list_insert_sorted("N/A", 0, 0);
        highscore_list_insert_sorted("N/A", 0, 0);
        highscore_list_insert_sorted("N/A", 0, 0);
        return;
    }
    char name[4];
    int score = 0, round = 0;
    while (fscanf(fp, "%3s %d %d\n", name, &score, &round) == 3) {
        highscore_list_insert_sorted(name, score, round);
    }
    fclose(fp);
}

void highscore_save(void) {
    FILE* fp = fopen(HIGHSCORE_FILE, "w");
    if (!fp) return;
    int count = 0;
    HighscoreNode* cur = g_highscore_head;
    while (cur && count < HIGHSCORE_SAVE_COUNT) {
        fprintf(fp, "%s %d %d\n", cur->data.name, cur->data.score, cur->data.round);
        cur = cur->next;
        count++;
    }
    fclose(fp);
}

int highscore_check_and_add(const char* name, int score, int round) {
    
    int position = 0;
    HighscoreNode* cur = g_highscore_head;
    while (cur && cur->data.score >= score) {
        position++;
        cur = cur->next;
    }
    if (position >= HIGHSCORE_SAVE_COUNT) return -1;
    highscore_list_insert_sorted(name, score, round);
    highscore_save();
    
    position = 0;
    cur = g_highscore_head;
    while (cur) {
        if (strncmp(cur->data.name, name, 3) == 0 && cur->data.score == score && cur->data.round == round) {
            return position;
        }
        position++;
        cur = cur->next;
    }
    return -1;
}

void highscore_draw(int y_start) {
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(30, y_start);
    printf("MELHORES PONTUAÇÕES");
    int i = 0;
    HighscoreNode* cur = g_highscore_head;
    while (cur && i < HIGHSCORE_DISPLAY_COUNT) {
        screenGotoxy(32, y_start + 2 + i);
        printf("%d. %s %d (Rodada %d)", i + 1, cur->data.name, cur->data.score, cur->data.round);
        cur = cur->next;
        i++;
    }
}
