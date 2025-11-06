#include "projectile.h"
#include "screen.h"
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
    /* nada a liberar por enquanto */
}

void projectileSpawn(int x, int y)
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
    /* se não houver slot livre, ignora o tiro */
}

void projectileUpdate(void)
{
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        if (!bullets[i].active) continue;
        bullets[i].y -= 1; /* move para cima */
        /* se chegou ao topo da área jogável, desativa */
        if (bullets[i].y <= SCRSTARTY + 1)
        {
            bullets[i].active = 0;
        }
    }
}

void projectileDraw(void)
{
    for (int i = 0; i < MAX_PROJECTILES; ++i)
    {
        if (!bullets[i].active) continue;
        screenGotoxy(bullets[i].x, bullets[i].y);
        printf("|");
    }
}
