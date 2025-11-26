#ifndef ENEMY_H
#define ENEMY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Inicialização / limpeza */
void enemyInit(void);
void enemyDestroy(void);

/* Atualiza e desenha inimigos */
void enemyUpdate(void);
void enemyDraw(void);


/* Retorna 1 se houver colisão com inimigo na posição (x,y) */
int enemyCheckCollision(int x, int y);

/* Retorna o round atual */
int enemy_get_current_round(void);

#ifdef __cplusplus
}
#endif

#endif