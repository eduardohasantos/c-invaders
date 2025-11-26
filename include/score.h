// ...existing code...
#ifndef SCORE_H
#define SCORE_H


#ifdef __cplusplus
extern "C" {
#endif

/* Estrutura para uma entrada de recorde */
typedef struct {
	char name[4];
	int score;
	int round;
} Highscore;

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

/* Funções de Highscore */
void highscore_load(void);
void highscore_save(void);
void highscore_draw(int y_start);
int highscore_check_and_add(const char* name, int score, int round);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
// ...existing code...