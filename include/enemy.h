#ifndef ENEMY_H
#define ENEMY_H

#ifdef __cplusplus
extern "C" {
#endif

 
void enemyInit(void);
void enemyDestroy(void);

 
void enemyUpdate(void);
void enemyDraw(void);


 
int enemyCheckCollision(int x, int y);

 
int enemy_get_current_round(void);

#ifdef __cplusplus
}
#endif

#endif