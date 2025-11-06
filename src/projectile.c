#include "projectile.h"
#include "screen.h"
#include "enemy.h"
#include <stdio.h>

#define MAX_PROJECTILES 16

typedef struct {
    int x;
    int y;
    int active;
} Projectile;

static Projectile bullets[MAX_PROJECTILES];

void projectileInit(void)
{
    for (int i = 0; i < MAX_PROJECTILES; ++i) bullets[i].active = 0;
}

void projectileDestroy(void)
{
}

void projectileCreate(int x, int y)
{
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        if (!bullets[i].active)
        {
            bullets[i].active = 1;
            bullets[i].x = x;
            bullets[i].y = y;
            return;
        }
    }
}

void projectileUpdate(void)
{
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        if (!bullets[i].active) continue;
        
        bullets[i].y -= 1;
        
        if (enemyCheckCollision(bullets[i].x, bullets[i].y)) {
            bullets[i].active = 0;
            continue;
        }
        
        if (bullets[i].y <= SCRSTARTY + 1)
        {
            bullets[i].active = 0;
        }
    }
}

void projectileDraw(void)
{
    screenSetColor(YELLOW, BLACK);
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        if (!bullets[i].active) continue;
        screenGotoxy(bullets[i].x, bullets[i].y);
        printf("|");
    }
    screenSetColor(WHITE, BLACK);
}
