// ...existing code...
#ifndef SCORE_H
#define SCORE_H


#ifdef __cplusplus
extern "C" {
#endif

 
typedef struct {
	char name[4];
	int score;
	int round;
} Highscore;

 
void score_init(void);

 
void score_add(int points);

 
int score_get(void);

 
void score_reset(void);

 
void score_draw(void);

 
void highscore_load(void);
void highscore_save(void);
void highscore_draw(int y_start);
int highscore_check_and_add(const char* name, int score, int round);

#ifdef __cplusplus
}
#endif

#endif
 