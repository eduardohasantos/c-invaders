#ifndef PROJECTILE_H
#define PROJECTILE_H

/* Inicializa o sistema de projéteis */
void projectileInit(void);

/* Libera recursos (se houver) */
void projectileDestroy(void);

/* Cria/atira um projétil na posição (x,y) */
void projectileSpawn(int x, int y);

/* Atualiza a posição dos projéteis (chamar periodicamente) */
void projectileUpdate(void);

/* Desenha projéteis ativos na tela */
void projectileDraw(void);

#endif
