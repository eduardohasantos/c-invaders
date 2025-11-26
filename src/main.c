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
#include "enemy_projectile.h"

typedef enum { STATE_GET_NAME, STATE_PLAYING, STATE_PAUSED, STATE_GAME_OVER } GameState;

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
    enemy_projectile_init();
    enemyInit();
    score_init();
    Player* player = create_player(10, 20);
    char playerName[4] = "AAA";
    int nameCharIndex = 0;

    int redraw = 1;
    const int minX = SCRSTARTX + 2;
    const int maxX = SCRENDX - 2;

    GameState state = STATE_GET_NAME;

    while (1) {
        // --- LÓGICA DE ESTADOS DO JOGO ---
        if (state == STATE_GET_NAME) {
            if (redraw) {
                screenClear();
                screenDrawBorders();
                screenSetColor(YELLOW, BLACK);
                screenGotoxy(25, 10);
                printf("INSIRA SEU NOME (3 LETRAS):");
                screenGotoxy(38, 12);
                printf("%c %c %c", playerName[0], playerName[1], playerName[2]);
                screenGotoxy(38 + (nameCharIndex * 2), 13);
                printf("^");
                screenUpdate();
                redraw = 0;
            }

            if (keyhit()) {
                int c = readch();
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    playerName[nameCharIndex] = (c >= 'a') ? c - 32 : c; // Converte para maiúscula
                    nameCharIndex++;
                    redraw = 1;
                }
                if (nameCharIndex >= 3) {
                    state = STATE_PLAYING;
                    redraw = 1;
                }
            }
            continue; // Pula o resto do loop
        }
        else if (state == STATE_PLAYING && timerHasElapsed(50)) {
            projectileUpdate();
            enemyUpdate();
            enemy_projectile_update();
            redraw = 1;

            // Verifica colisão do projétil inimigo com o jogador e se o jogador ainda tem vidas
            if (enemy_projectile_check_collision(player->x, player->y)) {
                player->lives--;
                if (player->lives <= 0) {
                    highscore_check_and_add(playerName, score_get(), enemy_get_current_round());
                    state = STATE_GAME_OVER;
                }
            }
        }

    if (keyhit()) {
    int c = readch();

    if (state == STATE_GAME_OVER) {
        if (c == 'q' || c == 'Q' || c == 27) {
            break; // Sair do jogo
        } else if (c == 'r' || c == 'R') {
            // Reiniciar o jogo
            enemyInit();
            projectileInit();
            enemy_projectile_init();
            score_reset();
            player->x = 10;
            player->y = 20;
            player->lives = 3;
            state = STATE_PLAYING;
            redraw = 1;
        }
        continue; // Ignora outras teclas
    }

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
        }
    } else if (state == STATE_PLAYING && (c == 'a' || c == 'A')) {
            player->x--;
            if (player->x < minX) player->x = minX;
            redraw = 1;
        } else if (state == STATE_PLAYING && (c == 'd' || c == 'D')) {
            player->x++;
            if (player->x > maxX) player->x = maxX;
            redraw = 1;
        } else if (state == STATE_PLAYING && c == ' ') {
            if (player_can_shoot()) {
                projectileCreate(player->x, player->y);
                player_shoot();
                redraw = 1;
            }
        }

        else if (c == 'p' || c == 'P') {
            if (state == STATE_PLAYING) {
                state = STATE_PAUSED;
                screenClear();
                screenDrawBorders();
                screenGotoxy(30, 10);
                printf("=== JOGO PAUSADO ===");
                screenGotoxy(23, 12);
                printf("=== PRESSIONE P PARA CONTINUAR ===");
                screenUpdate();
            } else if (state == STATE_PAUSED) {
                state = STATE_PLAYING;
                redraw = 1;
            }
        }
        // Adiciona a funcionalidade de "Novo Jogo" com a tecla 'N'
        else if (c == 'r' || c == 'R') {
            // Reinicia completamente o jogo para a tela de nome
            enemyInit();
            projectileInit();
            enemy_projectile_init();
            score_reset();
            player->x = 10;
            player->y = 20;
            player->lives = 3;
            nameCharIndex = 0; // Reseta o índice para inserção do nome
            state = STATE_GET_NAME;
            redraw = 1;
        }
    }

    if (redraw && (state == STATE_PLAYING || state == STATE_PAUSED)) {
            screenClear();
            screenDrawBorders();
            enemyDraw();
            projectileDraw();
            enemy_projectile_draw();
            draw_player(player);
            score_draw(); // Desenha a pontuação
            
            // Desenha as vidas do jogador
            screenSetColor(WHITE, BLACK);
            screenGotoxy(MAXX - 15, 2);
            printf("Vidas: %d", player->lives);

            // Desenha a ronda atual
            screenSetColor(WHITE, BLACK);
            screenGotoxy(38, 2);
            printf("Rodada: %d", enemy_get_current_round());

            screenUpdate();
            redraw = 0;
    } else if (redraw && state == STATE_GAME_OVER) {
        screenClear();
        screenDrawBorders();
        screenSetColor(RED, BLACK);
        screenGotoxy(32, 5);
        printf("=== GAME OVER ===");
        
        // Mostra a pontuação final de forma destacada
        char final_score_text[32];
        snprintf(final_score_text, sizeof(final_score_text), "SUA PONTUACAO: %d", score_get());
        screenGotoxy(40 - (strlen(final_score_text) / 2), 8);
        printf("%s", final_score_text);

        highscore_draw(11); // Desenha os recordes a partir da linha 11
        screenGotoxy(25, 20);
        printf("Pressione 'R' para reiniciar ou 'Q' para sair");
        screenUpdate();
        redraw = 0;
    }
}

    enemyDestroy();
    projectileDestroy();
    enemy_projectile_destroy();
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    return 0;

}
