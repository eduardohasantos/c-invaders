#include "player.h"
#include <stdlib.h>
#include "screen.h"

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