#include "enemy.h"
#include "screen.h"
#include <stdio.h>

#define ENEMY_ROWS 5
#define ENEMY_COLS 11
#define ENEMY_SPACING_X 1
#define ENEMY_SPACING_Y 1
#define ENEMY_CHAR 'M'
#define ENEMY_BASE_SPEED 2

typedef struct {
    int x, y;
    int active;
} Enemy;

static Enemy enemies[ENEMY_ROWS][ENEMY_COLS];

static int moveDirection = 1;
static int updateCounter = 0;
static int enemyValue = 10;
static int roundsCleared = 0;
static int roundWon = 0;
static double enemySpeed = ENEMY_BASE_SPEED;
static unsigned int roundWinTime = 0;
static unsigned int roundWinTimer = 0;


static void respawnEnemies(void)
{
    int startX = SCRSTARTX + 5;
    int startY = SCRSTARTY + 2;
    
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            enemies[row][col].x = startX + (col * ENEMY_SPACING_X);
            enemies[row][col].y = startY + (row * ENEMY_SPACING_Y);
            enemies[row][col].active = 1;
        }
    }
    roundWon = 0;
}

void enemyInit(void)
{
    enemyValue = 10;
    roundsCleared = 0;
    moveDirection = 1;
    updateCounter = 0;
    enemySpeed = ENEMY_BASE_SPEED;
    roundWon = 0;
    roundWinTime = 0;
    roundWinTimer = 0;
    respawnEnemies();
}

void enemyDestroy(void)
{

}

void enemyUpdate(void) {
    if (roundWon) {
        if (roundWinTime) {
            if (roundWinTimer == 0) {
                roundWinTimer = timerGetDelta();
            }
            // Espera 3 segundos (3000 ms) após round ganho
            if (timerGetDelta() - roundWinTimer >= 3000) {
                enemySpeed *= 1.3; // 30% mais rápido a cada round
                respawnEnemies();
                roundWinTime = 0;
                roundWinTimer = 0;
            }
        }
        return;
    }

    updateCounter++;
    int updateThreshold = (int)(15 / enemySpeed);
    if (updateThreshold < 1) updateThreshold = 1;
    if (updateCounter < updateThreshold) return;
    updateCounter = 0;

    int needsFlip = 0;
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (!enemies[row][col].active) continue;
            int nextX = enemies[row][col].x + moveDirection;
            if (nextX <= SCRSTARTX + 1 || nextX >= SCRENDX - 1) {
                needsFlip = 1;
                break;
            }
        }
        if (needsFlip) break;
    }

    if (needsFlip) {
        moveDirection *= -1;
    }

    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (!enemies[row][col].active) continue;
            enemies[row][col].x += moveDirection * (int)enemySpeed;
        }
    }
}

void enemyDraw(void)
{
    if (roundWon) {
        screenSetColor(GREEN, BLACK);
        screenGotoxy(30, 12);
        printf("ROUND GANHO!");
        screenSetColor(WHITE, BLACK);
        return;
    }
    screenSetColor(RED, BLACK);
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (!enemies[row][col].active) continue;
            screenGotoxy(enemies[row][col].x, enemies[row][col].y);
            printf("%c", ENEMY_CHAR);
        }
    }
    screenSetColor(WHITE, BLACK);
}

int enemyCheckCollision(int x, int y)
{
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (!enemies[row][col].active) continue;
            if (enemies[row][col].x == x && enemies[row][col].y == y) {
                enemies[row][col].active = 0;
                int awarded = enemyValue;

                int anyAlive = 0;
                for (int r = 0; r < ENEMY_ROWS && !anyAlive; r++) {
                    for (int c = 0; c < ENEMY_COLS; c++) {
                        if (enemies[r][c].active) { anyAlive = 1; break; }
                    }
                }

                if (!anyAlive && !roundWon) {
                    roundsCleared++;
                    enemyValue += 5;
                    roundWon = 1;
                    roundWinTime = 1; // Marca que o round foi ganho
                    // O respawn será feito no enemyUpdate após 3s
                }

                return awarded;
            }
        }
    }
    return 0;
}