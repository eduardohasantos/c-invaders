#ifndef ENEMY_H
#define ENEMY_H

void enemyInit(void);
void enemyDestroy(void);
void enemyUpdate(void);
void enemyDraw(void);
int enemyCheckCollision(int x, int y);

#endif
