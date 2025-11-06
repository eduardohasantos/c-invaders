#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;
    char symbol;
} Player;

Player* create_player(int x, int y);
void draw_player(Player* p);

#endif