#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_NUMBER 10 
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 20
#define ENEMY_MOVE 20
#define ENEMY_BORDER 20
#define ENEMY_DROP 20 //distance descendue par cran

#define ENEMY_BULLET_WIDTH 5
#define ENEMY_BULLET_HEIGHT 20
#define ENEMY_BULLET_SPEED 600.0f

typedef struct
{
    float x, y;
    int w, h;
    bool alive;
} Enemy;

void new_wave(Enemy* wave, Uint8 lignes, Uint8* enemy_number) ;

#endif