#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "time.h"
#include "player.h"
#include "projectile.h"


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
    timerInit(50);
    projectileInit();

    Player* player = create_player(10, 20);

    int redraw = 1;
    /* limites jogáveis (dentro das bordas desenhadas) */
    const int minX = SCRSTARTX + 1;
    const int maxX = SCRENDX - 1;

    while (1) {
        /* redesenhar por timer */
        if (timerTimeOver()) {
            /* atualiza projéteis e marca redraw */
            projectileUpdate();
            redraw = 1;
        }

        /* entrada de usuário */
        if (keyhit()) {
            int c = readch();
            if (c == 27) {
                /* possível sequência de escape (setas) */
                if (keyhit()) {
                    int c2 = readch();
                    if (c2 == '[' && keyhit()) {
                        int dir = readch();
                        if (dir == 'C') player->x++; /* right */
                        else if (dir == 'D') player->x--; /* left */
                        /* garantir limites */
                        if (player->x < minX) player->x = minX;
                        if (player->x > maxX) player->x = maxX;
                        redraw = 1;
                    }
                } else {
                    /* ESC sozinho -> sair */
                    break;
                }
            } else if (c == 'a' || c == 'A') {
                player->x--;
                if (player->x < minX) player->x = minX;
                redraw = 1;
            } else if (c == 'd' || c == 'D') {
                player->x++;
                if (player->x > maxX) player->x = maxX;
                redraw = 1;
            } else if (c == ' ' ) {
                /* espaço: atira a partir da posição do jogador (acima dele) */
                projectileSpawn(player->x, player->y - 1);
                redraw = 1;
            }
        }

        if (redraw) {
            screenClear();
            screenDrawBorders();
            projectileDraw();
            draw_player(player);
            screenUpdate();
            redraw = 0;
        }
    }

    projectileDestroy();
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    return 0;

}
