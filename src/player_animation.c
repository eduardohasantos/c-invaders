#include "player_animation.h"
#include "screen.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

static void sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep((useconds_t)ms * 1000);
#endif
}

void player_hit_animation(Player* p) {
    for (int i = 0; i < 2; i++) {
        
        screenSetColor(RED, BLACK);
        screenGotoxy(p->x, p->y);
        printf("X");
        screenUpdate();
        sleep_ms(120);
        
        screenSetColor(WHITE, BLACK);
        screenGotoxy(p->x, p->y);
        printf("%c", p->symbol);
        screenUpdate();
        sleep_ms(80);
    }
    
    screenSetColor(WHITE, BLACK);
    screenGotoxy(p->x, p->y);
    printf("%c", p->symbol);
    screenUpdate();
}
