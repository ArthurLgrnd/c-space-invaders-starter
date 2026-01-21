#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entity.h"
#include "game.h"
#include "enemy.h"


void new_wave(Entity* wave, Uint8 lignes ){
    for (int i=0 ; i<lignes*ENEMY_NUMBER ; i++){
        wave[i].x = 10 + (i%ENEMY_NUMBER) * (ENEMY_WIDTH + 20) ;
        wave[i].y = 10 + i/ENEMY_NUMBER * (ENEMY_HEIGHT +10) ;
        wave[i].vx = 0 ;
        wave[i].vy = 0 ;
        wave[i].w = ENEMY_WIDTH ;
        wave[i].h = ENEMY_HEIGHT ;
    }
}

