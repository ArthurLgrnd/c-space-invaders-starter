#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_NUMBER 10 
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 20
#define ENEMY_MOVE 20
#define ENEMY_BORDER 20
#define ENEMY_DROP 20 //distance descendue par cran



typedef struct
{
    float x, y;
    int w, h;
    bool alive;
} Enemy;

void new_wave(Enemy* wave, Uint8 lignes) ;

#endif