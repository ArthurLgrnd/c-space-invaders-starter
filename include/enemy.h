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
    CLASSIC=0, /*ok*/
    SHIELD=1, /*ok*/
    BR_SHIELD=2, /*ok*/
    NO_SHIELD=3, /*ok*/
    NINJA=4, /*Rapide à descendre*/   /*~~ok, juste voir si faire en sorte que target ne soit jamais un ninja(faire une 2ème boucle)*/
    FAST=5, /*Rapide sur les côtés*/   /*~~ok*/
    FAST_SHOOT=6, /*ok*/
    MILITARY=7, /*Tir plus souvent*/   /*ok*/
    HEALER=8 /*ok*/
} Enemy_types ;

typedef struct
{
    float x, y;
    int w, h;
    bool alive;
    Enemy_types type;
} Enemy;

typedef struct
{
    float x, y;
    float vy;
    int w, h;
    bool mushroom;
} Enemy_bullet;


void new_wave(Enemy* wave, Uint8 lignes, Uint8* enemy_number) ;
bool new_enemy_bullet(Enemy* wave, Uint8 enemy_compt, Uint8* enemy_bullet_compt, Uint8* enemy_bullet_max, Enemy_bullet** enemy_bullet, Uint8 lignes) ;
void update_enemy(Enemy* wave, Uint8 lignes, short* move_sens, bool* last_move_drop, float* move_time) ;
void update_fast_enemy(Enemy* wave, Uint8 lignes, short move_sens);
void ninja_dash(Enemy* wave, Uint8 lignes, Uint8 enemy_compt) ;
bool enemy_down(Enemy* wave, Uint8 lignes) ;



#endif