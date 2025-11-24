#include "enemy.h"
#include "screen.h"
#include <stdio.h>

#define ENEMY_ROWS 5
#define ENEMY_COLS 11
#define ENEMY_SPACING_X 1
#define ENEMY_SPACING_Y 1
#define ENEMY_CHAR 'M'
#define ENEMY_SPEED 1

typedef struct {
    int x, y;
    int active;
} Enemy;

static Enemy enemies[ENEMY_ROWS][ENEMY_COLS];
static int moveDirection = 1;
static int updateCounter = 0;

static int enemyValue = 10;
static int roundsCleared = 0;


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
}

void enemyInit(void)
{
    enemyValue = 10;
    roundsCleared = 0;
    moveDirection = 1;
    updateCounter = 0;

    respawnEnemies();
}

void enemyDestroy(void)
{

}

void enemyUpdate(void) {

    updateCounter++;
    if (updateCounter < 15) return;
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
            enemies[row][col].x += moveDirection * ENEMY_SPEED;
        }
    }
}

void enemyDraw(void)
{
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

                if (!anyAlive) {
                    roundsCleared++;
                    enemyValue += 5;
                    respawnEnemies();
                }

                return awarded;
            }
        }
    }
    return 0;
}