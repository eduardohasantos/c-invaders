// ...existing code...
#ifndef SCORE_H
#define SCORE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Inicializa o score (zera) */
void score_init(void);

/* Adiciona pontos ao score */
void score_add(int points);

/* Retorna o score atual */
int score_get(void);

/* Reseta o score para zero */
void score_reset(void);

/* Desenha o score na tela (chame após screenUpdate()). */
void score_draw(void);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
// ...existing code...