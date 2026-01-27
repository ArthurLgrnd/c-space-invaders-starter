#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_NUMBER 10 
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 20

typedef struct
{
    float x, y;
    int w, h;
} Enemy;

void new_wave(Enemy* wave, Uint8 lignes) ;

#endif