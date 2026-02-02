#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "entity.h"

#define ENEMY_NUMBER 10 
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 32
#define ENEMY_MOVE 20
#define ENEMY_BORDER 20
#define ENEMY_DROP 42 //distance descendue par cran

#define ENEMY_BULLET_WIDTH 5
#define ENEMY_BULLET_HEIGHT 20
#define ENEMY_BULLET_SPEED 600.0f

typedef enum {
    CLASSIC=0,
    SHIELD=1,
    BR_SHIELD=2,
    NO_SHIELD=3,
    NINJA=4, /*Rapide à descendre*/
    FAST=5, /*Rapide sur les côtés*/
    FAST_SHOOT=6,
    MILITARY=7, /*Tir plus souvent*/
    HEALER=8 
} Enemy_types ;

typedef struct
{
    float x, y;
    int w, h;
    bool alive;
    Enemy_types type;
} Enemy;


void new_wave(Enemy* wave, Uint8 lignes, Uint8* enemy_number) ;
void new_enemy_bullet(Enemy* wave, Uint8 enemy_compt, Uint8* enemy_bullet_compt, Entity* enemy_bullet);
void update_enemy(Enemy* wave, Uint8 lignes, short* move_sens, bool* last_move_drop, float* move_time) ;
bool enemy_down(Enemy* wave, Uint8 lignes) ;



#endif