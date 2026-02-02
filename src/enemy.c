#include <stdbool.h>
#include "entity.h"
#include "game.h"
#include "enemy.h"


void new_wave(Enemy* wave, Uint8 lignes, Uint8* enemy_compt){
    for (int i=0 ; i<lignes*ENEMY_NUMBER ; i++){
        wave[i].x = 20 + (i%ENEMY_NUMBER) * (ENEMY_WIDTH + 20) ;
        wave[i].y = 80 + i/ENEMY_NUMBER * (ENEMY_HEIGHT +10) ;
        wave[i].alive = true ;
        wave[i].w = ENEMY_WIDTH ;
        wave[i].h = ENEMY_HEIGHT ;
        wave[i].type = 1 ;
    }
    *enemy_compt=lignes*ENEMY_NUMBER ;
}


void new_enemy_bullet(Enemy* wave, Uint8 enemy_compt, Uint8* enemy_bullet_compt, Entity* enemy_bullet){
    if (enemy_compt > 0){
        int shooter = rand() % enemy_compt ;
        Uint8 i = 0 ;
        Uint8 j = 0 ;
        while (i<=shooter){
            if (wave[j].alive==true){
                i+=1 ;
            }
            j+=1 ;
        } //choix d'un ennemi en vie au hasard
        enemy_bullet[*enemy_bullet_compt].x = wave[j-1].x + ENEMY_WIDTH/2 ;
        enemy_bullet[*enemy_bullet_compt].y = wave[j-1].y + ENEMY_HEIGHT ;
        enemy_bullet[*enemy_bullet_compt].vx = 0 ;
        enemy_bullet[*enemy_bullet_compt].vy = ENEMY_BULLET_SPEED ;
        enemy_bullet[*enemy_bullet_compt].h = ENEMY_BULLET_HEIGHT ;
        enemy_bullet[*enemy_bullet_compt].w = ENEMY_BULLET_WIDTH ;
        *enemy_bullet_compt+=1 ;
    }
    
}


void update_enemy(Enemy* wave, Uint8 lignes, short* move_sens, bool* last_move_drop, float* move_time){
    if (!*last_move_drop){
        for (Uint8 i=0 ; i<lignes*ENEMY_NUMBER ; i++){
            if (wave[i].alive==1 && (wave[i].x<=ENEMY_BORDER || wave[i].x>=SCREEN_WIDTH-ENEMY_BORDER-ENEMY_WIDTH)){
                for (Uint8 j=0 ; j<lignes*ENEMY_NUMBER ; j++){
                    wave[j].y+=ENEMY_DROP ;
                }
                *move_sens*=-1 ;
                *last_move_drop = true ;
                *move_time *=0.9 ;
                break ;
            }
        }
    }
    else{*last_move_drop=false;}
    if (!*last_move_drop){
        for (Uint8 i=0 ; i<lignes*ENEMY_NUMBER ; i++){
            if (wave[i].alive==1){
                wave[i].x+=ENEMY_MOVE* *move_sens ;
            }
        }
    }
}

bool enemy_down(Enemy* wave, Uint8 lignes){
    for (int8_t i = lignes * ENEMY_NUMBER - 1 ; i>=0 ; i-=1){ /*Parcours à l'envers pour commencer par les plus bas et stopper dès qu'un en vie est trouvé*/
        if (wave[i].alive==1){
            if (wave[i].y + wave[i].h >= SCREEN_HEIGHT - 60){
                return true ;
            }
            break ;
        }
    }
    return false ;
}
