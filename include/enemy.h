#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "entity.h"

#define ENEMY_NUMBER 10 
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 32  /*Recommandé *4/5 par rapport à ENEMY_WIDTH*/
#define ENEMY_MOVE 20
#define ENEMY_BORDER 20
#define ENEMY_DROP 42 //distance descendue par cran

#define BONUS_WIDTH 60
#define BONUS_HEIGHT 26 /*Recommandé ~*0.44 par rapport à BONUS_WIDTH*/
#define BONUS_SPEED 200.0f

#define ENEMY_BULLET_WIDTH 5
#define ENEMY_BULLET_HEIGHT 20
#define ENEMY_BULLET_SPEED 500.0f

typedef enum {
    CLASSIC=0,
    SHIELD=1,
    MILITARY=2, /*Tir plus souvent*/
    FAST_SHOOT=3,
    FAST=4, /*Rapide sur les côtés*/
    HEALER=5,
    BR_SHIELD=6,
    NO_SHIELD=7,
    BONUS=8
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

#include "game.h"


void new_wave(Enemy* wave, Round* round, Uint8* enemy_compt, float* round_move_time, float* var_move_time) ;
bool new_enemy_bullet(Enemy* wave, Uint8 enemy_compt, Uint8* enemy_bullet_compt, Uint8* enemy_bullet_max, Enemy_bullet** enemy_bullet, Round round) ;
void update_enemy(Enemy* wave, Round round, short* move_sens, bool* last_move_drop, float* move_time) ;
void update_fast_enemy(Enemy* wave, Round round, short* fast_move_sens, bool* fast_last_move_drop);
void new_bonus(Enemy* bonus_enemy, float* bonus_time, short* bonus_sens);
bool enemy_down(Enemy* wave, Round round) ;



#endif