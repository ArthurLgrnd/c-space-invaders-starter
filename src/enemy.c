#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entity.h"
#include "game.h"
#include "enemy.h"


void new_wave(Enemy* wave, Uint8 lignes, Uint8* enemy_compt){
    for (int i=0 ; i<lignes*ENEMY_NUMBER ; i++){
        wave[i].x = 20 + (i%ENEMY_NUMBER) * (ENEMY_WIDTH + 20) ;
        wave[i].y = 10 + i/ENEMY_NUMBER * (ENEMY_HEIGHT +10) ;
        wave[i].alive = true ;
        wave[i].w = ENEMY_WIDTH ;
        wave[i].h = ENEMY_HEIGHT ;
    }
    *enemy_compt=lignes*ENEMY_NUMBER ;
}

