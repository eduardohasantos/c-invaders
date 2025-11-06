#include "player.h"
#include <stdlib.h>
#include "screen.h"
#include "timer.h"

#define SHOOT_COOLDOWN 500

static unsigned int lastShotTime = 0;

Player* create_player(int x, int y) {
    Player* p = malloc(sizeof(Player));
    p->x = x;
    p->y = y;
    p->symbol = 'A';
    return p;
}

void draw_player(Player* p) {
    screenGotoxy(p->x, p->y);
    printf("%c", p->symbol);
}

int player_can_shoot(void) {
    unsigned int currentTime = timerGetDelta();
    if (currentTime - lastShotTime >= SHOOT_COOLDOWN) {
        return 1;
    }
    return 0;
}

void player_shoot(void) {
    lastShotTime = timerGetDelta();
}