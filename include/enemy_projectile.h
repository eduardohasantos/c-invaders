// Permite acesso externo ao cooldown dinâmico
extern double enemy_projectile_cooldown;
#ifndef ENEMY_PROJECTILE_H
#define ENEMY_PROJECTILE_H

void enemy_projectile_init(void);
void enemy_projectile_destroy(void);
void enemy_projectile_create(int x, int y);
void enemy_projectile_update(void);

void enemy_projectile_draw(void);
int enemy_projectile_check_collision(int x, int y);
void enemy_projectile_next_round(void);

#endif
