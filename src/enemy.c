#include <stdbool.h>
#include <stdio.h>
#include "entity.h"
#include "enemy.h"
#include "game.h"





void new_wave(Enemy* wave, Round* round, Uint8* enemy_compt, float* round_move_time, float* var_move_time){
    round->number+=1;
    if (round->number<=15){*round_move_time*=0.955;} /*Facteur permettant d'avoir une division par deux au bout de 15 rounds*/
    *var_move_time = *round_move_time ;
    if (round->number % 5 ==0){round->total_enemy = 1 ;}
    else if (round->number==1){round->total_enemy = 2 * ENEMY_NUMBER ;}
    else if (round->number<=9){round->total_enemy = 3 * ENEMY_NUMBER ;}
    else {round->total_enemy = 4 * ENEMY_NUMBER ;}

    for (int i=0 ; i<round->total_enemy; i++){
        wave[i].x = 20 + (i%ENEMY_NUMBER) * (ENEMY_WIDTH + 20) ;
        wave[i].y = 80 + i/ENEMY_NUMBER * (ENEMY_HEIGHT +10) ;
        wave[i].alive = true ;
        wave[i].w = ENEMY_WIDTH ;
        wave[i].h = ENEMY_HEIGHT ;
        wave[i].type = CLASSIC ;
    }

    Uint8 repet = 0 ;
    Uint8 random;
    switch(round->number){
        case 2:
            wave[rand()%round->total_enemy].type = HEALER;
            break ;
        case 3:
            wave[2*ENEMY_NUMBER+1].type = SHIELD ;
            wave[round->total_enemy-2].type = SHIELD ; 
            break ;
        case 4:
            for (Uint8 i=ENEMY_NUMBER; i < 2*ENEMY_NUMBER ; i+=2){wave[i].type=SHIELD;}
            for (Uint8 i=2*ENEMY_NUMBER+1; i < 3*ENEMY_NUMBER ; i+=2){wave[i].type=SHIELD;}
            break ;
        case 6:
            wave[1].type=MILITARY;
            wave[ENEMY_NUMBER-2].type=MILITARY;
            while(repet<4){
                do{ 
                    random=ENEMY_NUMBER + rand() % (2*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = SHIELD;
                repet += 1 ;
            }
            do{ 
                random=rand() % round->total_enemy;
            } while (wave[random].type != CLASSIC) ;
            wave[random].type = HEALER;
            break ;
        case 7:
            wave[0].type=MILITARY;
            wave[3].type=MILITARY;
            wave[ENEMY_NUMBER-1].type=MILITARY;
            wave[ENEMY_NUMBER-4].type=MILITARY;

            while(repet<6){
                do{ 
                    random=ENEMY_NUMBER + rand() % (2*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = SHIELD;
                repet += 1 ;
            }
            break ;
        case 8:
            wave[1].type = FAST_SHOOT;
            wave[ENEMY_NUMBER-2].type = FAST_SHOOT;
            wave[(int)(ENEMY_NUMBER/2)].type = FAST_SHOOT;
            while(repet<4){
                do{ 
                    random=ENEMY_NUMBER + rand() % (2*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = SHIELD;
                repet += 1 ;
            }
            break ;
        case 9:
            wave[1].type=FAST_SHOOT;
            wave[ENEMY_NUMBER-2].type=FAST_SHOOT;
            wave[3].type=MILITARY;
            wave[ENEMY_NUMBER-4].type=MILITARY;
            wave[ENEMY_NUMBER].type=MILITARY;
            wave[2*ENEMY_NUMBER-1].type=MILITARY;
            wave[ENEMY_NUMBER+2].type=FAST_SHOOT;
            wave[2*ENEMY_NUMBER-3].type=FAST_SHOOT;
            wave[2*ENEMY_NUMBER].type=SHIELD;
            wave[3*ENEMY_NUMBER-1].type=SHIELD;
            wave[2*ENEMY_NUMBER+2].type=SHIELD;
            wave[3*ENEMY_NUMBER-3].type=SHIELD;
            
    }


    *enemy_compt=round->total_enemy ;
    
}


bool new_enemy_bullet(Enemy* wave, Uint8 enemy_compt, Uint8* enemy_bullet_compt, Uint8* enemy_bullet_max, Enemy_bullet** enemy_bullet, Round round){
    if (enemy_compt > 0){
        if (*enemy_bullet_max == *enemy_bullet_compt){
            *enemy_bullet_max += 1 ;
            Enemy_bullet* tmp = realloc(*enemy_bullet, sizeof(Enemy_bullet)**enemy_bullet_max) ;
            if (tmp == NULL){
                SDL_Log("Erreur realloc enemy_bullet");
                return false;
            }
            *enemy_bullet=tmp ;
        }
        int shooter = rand() % enemy_compt ;
        Uint8 i = 0 ;
        Uint8 j = 0 ;
        while ( i <=shooter){
            if (wave[j].alive==true){
                i+=1 ;
            }
            j+=1 ;
        } /*choix d'un ennemi en vie au hasard*/
        (*enemy_bullet)[*enemy_bullet_compt].x = wave[j-1].x + ENEMY_WIDTH/2 ;
        (*enemy_bullet)[*enemy_bullet_compt].y = wave[j-1].y + ENEMY_HEIGHT ;
        if (wave[j-1].type == FAST_SHOOT){
            (*enemy_bullet)[*enemy_bullet_compt].vy = 2 * ENEMY_BULLET_SPEED ;
        }
        else{
            (*enemy_bullet)[*enemy_bullet_compt].vy = ENEMY_BULLET_SPEED ;
        }
        if (wave[j-1].type == HEALER){
            (*enemy_bullet)[*enemy_bullet_compt].vy = ENEMY_BULLET_SPEED / 3 ;
            (*enemy_bullet)[*enemy_bullet_compt].h = 40 ;
            (*enemy_bullet)[*enemy_bullet_compt].w = 40 ;
            (*enemy_bullet)[*enemy_bullet_compt].mushroom = true ;
            wave[j-1].type = CLASSIC ;
        }
        else{
            (*enemy_bullet)[*enemy_bullet_compt].h = ENEMY_BULLET_HEIGHT ;
            (*enemy_bullet)[*enemy_bullet_compt].w = ENEMY_BULLET_WIDTH ;
            (*enemy_bullet)[*enemy_bullet_compt].mushroom = false ;
        }
        *enemy_bullet_compt+=1 ;

        /*tir des ennemis MILITAIRE*/
        for (Uint8 k=0 ; k<round.total_enemy ; k++){
            if (wave[k].alive==1 && wave[k].type==MILITARY && k!=j-1){
                if (rand()%4==0){ /*1 chance sur 4*/
                    if (*enemy_bullet_max == *enemy_bullet_compt){
                        *enemy_bullet_max+=1 ;
                        Enemy_bullet* tmp = realloc(*enemy_bullet, sizeof(Enemy_bullet)**enemy_bullet_max) ;
                        if (tmp == NULL){
                            SDL_Log("Erreur realloc enemy_bullet");
                            return false;
                        }
                        *enemy_bullet=tmp ;
                    }
                    (*enemy_bullet)[*enemy_bullet_compt].x = wave[k].x + ENEMY_WIDTH/2 ;
                    (*enemy_bullet)[*enemy_bullet_compt].y = wave[k].y + ENEMY_HEIGHT ;
                    (*enemy_bullet)[*enemy_bullet_compt].vy = ENEMY_BULLET_SPEED ;
                    (*enemy_bullet)[*enemy_bullet_compt].h = ENEMY_BULLET_HEIGHT ;
                    (*enemy_bullet)[*enemy_bullet_compt].w = ENEMY_BULLET_WIDTH ;
                    (*enemy_bullet)[*enemy_bullet_compt].mushroom = false ;
                    *enemy_bullet_compt+=1 ;
                }
            }
        }
    }
    return true ; 
}


void update_enemy(Enemy* wave, Round round, short* move_sens, bool* last_move_drop, float* move_time){
    if (!*last_move_drop){
        for (Uint8 i=0 ; i<round.total_enemy ; i++){
            if (wave[i].alive==1 && (wave[i].x<=ENEMY_BORDER || wave[i].x>=SCREEN_WIDTH-ENEMY_BORDER-ENEMY_WIDTH)){
                for (Uint8 j=0 ; j<round.total_enemy ; j++){
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
        for (Uint8 i=0 ; i<round.total_enemy ; i++){
            if (wave[i].alive==1){
                wave[i].x+=ENEMY_MOVE* *move_sens ;
            }
        }
    }
}

void update_fast_enemy(Enemy* wave, Round round, short move_sens){
    for (Uint8 i=0 ; i<round.total_enemy ; i++){
        if (wave[i].type == FAST){
            wave[i].x+=move_sens * ENEMY_MOVE;
        }
    }
}

/*Faire modification pour que seul un NINJA choisi au pif bouge à chaque répétition + faire gaffe à enemy_compt >1*/
void ninja_dash(Enemy* wave, Round round, Uint8 enemy_compt){
    Uint8 Ninja_compt = 0 ;
    Uint8* Ninja_list = NULL ;
    Uint8 target = rand() % enemy_compt; /*Rang parmis les survivants de l'invaders donc le NINJA va s'approcher*/
    Uint8 target_number ; /*Rang dans wave[]*/
    Uint8 i=0;
    for (Uint8 k=0 ; k<round.total_enemy ; k++){
        if (wave[k].alive==true){
            if(i==target){
                target_number = k ;
            }
            i+=1 ;
            if (wave[k].type == NINJA){ 
            Ninja_compt+=1 ;
            Ninja_list = realloc(Ninja_list, sizeof(Uint8)*Ninja_compt);
            if(Ninja_list==NULL){
                SDL_Log("Erreur realloc Ninja_list") ;
            }
            Ninja_list[Ninja_compt-1]=k ;
            }
        }
    }
    if (Ninja_compt>0){
        Uint8 choosen_ninja = Ninja_list[rand() % Ninja_compt] ; /*Rang dans wave[] du NINJA qui va se téléporter*/
        free(Ninja_list) ;
        if(wave[target].type!=NINJA){ /*Pas de mouvement si target est un NINJA car il n'est probablement plus dans sa position initiale*/
            int8_t new_pos = target_number;
            int8_t haut_bas = rand() % 2;
            if(haut_bas==0){haut_bas=-1;} /*-1 si va en au-dessus de la target, 1 si va en-dessous*/
            while (wave[new_pos].alive==1 && wave[new_pos].type!=NINJA){
                new_pos+=haut_bas*ENEMY_NUMBER ;
                if (new_pos>=round.total_enemy || new_pos<0) {break ;} 
            }
            wave[choosen_ninja].x = wave[target_number].x ;
            wave[choosen_ninja].y = wave[target_number].y + (new_pos - target_number)/10 * (ENEMY_HEIGHT + 10) ;
        }
    }
}

bool enemy_down(Enemy* wave, Round round){
    for (int8_t i = round.total_enemy - 1 ; i>=0 ; i-=1){ /*Parcours à l'envers pour commencer par les plus bas et stopper dès qu'un en vie est trouvé*/
        if (wave[i].alive==1){
            if (wave[i].y + wave[i].h >= SCREEN_HEIGHT - 60){
                return true ;
            }
            break ;
        }
    }
    return false ;
}
