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

#define ENEMY_BULLET_WIDTH 5
#define ENEMY_BULLET_HEIGHT 20
#define ENEMY_BULLET_SPEED 600.0f

typedef enum {
    CLASSIC=0, /*ok 10*/
    SHIELD=1, /*ok*/
    MILITARY=2, /*Tir plus souvent*/   /*ok 30*/
    FAST_SHOOT=3, /*ok 30*/
    NINJA=4, /*Rapide à descendre*/   /*~~ok 50, juste voir si faire en sorte que target ne soit jamais un ninja(faire une 2ème boucle) || autre idée de refonte : choisi une colonne au hasard et se place en haut ou bas parmis les vivants non NINJA*/
    FAST=5, /*Rapide sur les côtés*/   /*~~ok 30*/
    HEALER=6, /*ok 10*/
    BR_SHIELD=7, /*ok*/
    NO_SHIELD=8 /*ok 30*/
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
void update_fast_enemy(Enemy* wave, Round round, short move_sens);
void ninja_dash(Enemy* wave, Round round, Uint8 enemy_compt) ;
bool enemy_down(Enemy* wave, Round round) ;



#endif