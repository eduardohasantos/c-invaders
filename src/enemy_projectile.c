#include "enemy_projectile.h"
#include "screen.h"
#include <stdio.h>
#include "player.h"
#include "timer.h"

#define MAX_ENEMY_PROJECTILES 8
#define ENEMY_PROJECTILE_CHAR 'o'
#define ENEMY_PROJECTILE_COLOR GREEN
#define ENEMY_PROJECTILE_BG BLACK
#define ENEMY_PROJECTILE_BASE_COOLDOWN 1200
#define ENEMY_PROJECTILE_BASE_SPEED 1
extern double SHOOT_COOLDOWN;

static struct {
    int x, y;
    int active;
    double speed;
    double y_accum;
} enemy_bullets[MAX_ENEMY_PROJECTILES];

static unsigned int lastEnemyShot = 0;
double enemy_projectile_speed = ENEMY_PROJECTILE_BASE_SPEED;
double enemy_projectile_cooldown = ENEMY_PROJECTILE_BASE_COOLDOWN;
static int current_round = 0;

void enemy_projectile_init(void) {
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; ++i) {
        enemy_bullets[i].active = 0;
        enemy_bullets[i].speed = ENEMY_PROJECTILE_BASE_SPEED;
        enemy_bullets[i].y_accum = 0.0;
    }
    lastEnemyShot = 0;
    enemy_projectile_speed = ENEMY_PROJECTILE_BASE_SPEED;
    enemy_projectile_cooldown = ENEMY_PROJECTILE_BASE_COOLDOWN;
    current_round = 0;
}

void enemy_projectile_destroy(void) {

}

void enemy_projectile_create(int x, int y) {
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; ++i) {
        if (!enemy_bullets[i].active) {
            enemy_bullets[i].active = 1;
            enemy_bullets[i].x = x;
            enemy_bullets[i].y = y;
            enemy_bullets[i].speed = enemy_projectile_speed;
            enemy_bullets[i].y_accum = 0.0;
            return;
        }
    }
}

void enemy_projectile_update(void) {
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; ++i) {
        if (!enemy_bullets[i].active) continue;
        enemy_bullets[i].y_accum += enemy_bullets[i].speed;
        while (enemy_bullets[i].y_accum >= 1.0) {
            enemy_bullets[i].y += 1;
            enemy_bullets[i].y_accum -= 1.0;
        }
        if (enemy_bullets[i].y >= SCRENDY - 1) {
            enemy_bullets[i].active = 0;
        }
    }
}

void enemy_projectile_next_round(void) {
    current_round++;
    enemy_projectile_cooldown /= 1.3;
    if (enemy_projectile_cooldown < 200) enemy_projectile_cooldown = 200;

    enemy_projectile_speed = ENEMY_PROJECTILE_BASE_SPEED;
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; ++i) {
        enemy_bullets[i].speed = enemy_projectile_speed;
    }
}

void enemy_projectile_draw(void) {
    screenSetColor(ENEMY_PROJECTILE_COLOR, ENEMY_PROJECTILE_BG);
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; ++i) {
        if (!enemy_bullets[i].active) continue;
        screenGotoxy(enemy_bullets[i].x, enemy_bullets[i].y);
        printf("%c", ENEMY_PROJECTILE_CHAR);
    }
    screenSetColor(WHITE, BLACK);
}

int enemy_projectile_check_collision(int x, int y) {
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; ++i) {
        if (!enemy_bullets[i].active) continue;
        if (enemy_bullets[i].x == x && enemy_bullets[i].y == y) {
            enemy_bullets[i].active = 0;
            return 1;
        }
    }
    return 0;
}
