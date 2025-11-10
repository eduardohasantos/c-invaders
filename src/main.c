#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "time.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include "score.h"


int x = 34, y = 12;
int incX = 1, incY = 1;

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");
}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main() {
    screenInit(1);
    keyboardInit();
    timerInit();
    projectileInit();
    enemyInit();
    score_init();
    Player* player = create_player(10, 20);

    int redraw = 1;
    const int minX = SCRSTARTX + 1;
    const int maxX = SCRENDX - 1;

    int pause = 0;  // 0 = jogando, 1 = pausado

while (1) {
    if (!pause && timerHasElapsed(50)) {
        projectileUpdate();
        enemyUpdate();
        redraw = 1;
    }

    if (keyhit()) {
    int c = readch();

    if (c == 27) {
        if (keyhit()) {
            int c2 = readch();
            if (c2 == '[' && keyhit()) {
                int dir = readch();
                if (dir == 'C') player->x++;
                else if (dir == 'D') player->x--;
                if (player->x < minX) player->x = minX;
                if (player->x > maxX) player->x = maxX;
                redraw = 1;
            }
        } else {
            break;
        }
    }

        else if (!pause && (c == 'a' || c == 'A')) {
            player->x--;
            if (player->x < minX) player->x = minX;
            redraw = 1;
        } else if (!pause && (c == 'd' || c == 'D')) {
            player->x++;
            if (player->x > maxX) player->x = maxX;
            redraw = 1;
        } else if (!pause && c == ' ') {
            if (player_can_shoot()) {
                projectileCreate(player->x, player->y - 1);
                player_shoot();
                redraw = 1;
            }
        }

        else if (c == 'p' || c == 'P') {
            pause = !pause;
            if (pause) {
                screenClear();
                screenDrawBorders();
                screenGotoxy(30, 10);
                printf("=== JOGO PAUSADO ===");
                screenGotoxy(23, 12);
                printf("=== PRESSIONE P PARA CONTINUAR ===");
                screenUpdate();
            } else {
                redraw = 1;
            }
        }
    }

    if (redraw) {
        screenClear();
        screenDrawBorders();
        enemyDraw();
        projectileDraw();
        draw_player(player);
        screenUpdate();     
        score_draw();   
        redraw = 0;
    }
}

    enemyDestroy();
    projectileDestroy();
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    return 0;

}
