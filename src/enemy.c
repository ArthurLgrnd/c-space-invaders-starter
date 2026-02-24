#include <stdbool.h>
#include <stdio.h>
#include "entity.h"
#include "enemy.h"
#include "game.h"


void new_wave(Enemy* wave, Round* round, Uint8* enemy_compt, float* round_move_time, float* var_move_time){
    round->number+=1;
    if (round->number<=15){*round_move_time*=0.955;} /*Facteur permettant d'avoir une division par deux au bout de 15 rounds*/
    *var_move_time = *round_move_time ;
    if (round->number % 5 ==0){round->total_enemy = 1 ;} /*Round boss*/
    else if (round->number==1){round->total_enemy = 2 * ENEMY_NUMBER ;}
    else if (round->number<=9){round->total_enemy = 3 * ENEMY_NUMBER ;}
    else {round->total_enemy = 4 * ENEMY_NUMBER ;}

    for (int i=0 ; i<round->total_enemy; i++){
        wave[i].x = 20 + (i%ENEMY_NUMBER) * (ENEMY_WIDTH + 20) ;
        wave[i].y = 120 + i/ENEMY_NUMBER * (ENEMY_HEIGHT +10) ;
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
            do{ 
                random=rand() % round->total_enemy;
            } while (wave[random].type != CLASSIC) ;
            wave[random].type = HEALER;
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
            do{ 
                random=rand() % round->total_enemy;
            } while (wave[random].type != CLASSIC) ;
            wave[random].type = HEALER;
            break ;
        case 11:
            for (Uint8 i=ENEMY_NUMBER*3 ; i<round->total_enemy ; i++){
                wave[i].type = FAST ;
            }
            break;
        case 12:
            for (Uint8 i=ENEMY_NUMBER*3 ; i<round->total_enemy ; i++){
                wave[i].type = FAST ;
            }
            while(repet<4){
                do{ 
                    random=rand() % (3*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = SHIELD;
                repet += 1 ;
            }
            repet = 0 ;
            while(repet<2){
                do{ 
                    random=rand() % (3*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = MILITARY;
                repet += 1 ;
            }
            do{ 
                random=rand() % (3*ENEMY_NUMBER);
            } while (wave[random].type != CLASSIC) ;
            wave[random].type = HEALER;
            break;
        case 13 :
            for (Uint8 i=ENEMY_NUMBER*3 ; i<round->total_enemy ; i++){
                wave[i].type = FAST ;
            }
            while(repet<8){
                do{ 
                    random=rand() % (3*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = SHIELD;
                repet += 1 ;
            }
            repet = 0 ;
            while(repet<6){
                do{ 
                    random=rand() % (3*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = MILITARY;
                repet += 1 ;
            }
            repet = 0 ;
            while(repet<3){
                do{ 
                    random=rand() % (3*ENEMY_NUMBER);
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = FAST_SHOOT;
                repet += 1 ;
            }
            break ;
        case 14 :
            while(repet<4){
                do{ 
                    random=rand() % round->total_enemy;
                } while (wave[random].type != CLASSIC) ;
                wave[random].type = HEALER;
                repet += 1 ;
            }
            break ;
    }
    if (round->number > 15 && round->number%5!=0){
        Uint8 fast_lines = rand()%3 ; //Nombre de lignes FAST aléatoire entre 0 et 2
        for (Uint8 i=ENEMY_NUMBER*(4-fast_lines) ; i<round->total_enemy ; i++){
                wave[i].type = FAST ;
            }
        for (Uint8 i=0 ; i<ENEMY_NUMBER*(4-fast_lines) ; i++){
                wave[i].type = rand()%4 ; //Choix aléatoire entre classique, shield, military et fast_shoot
            }
        wave[rand()%(ENEMY_NUMBER*(4-fast_lines))].type = HEALER ; //Un healer au hasard parmis ceux qui ne sont pas des FAST
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
            if ((wave[i].type != FAST) && (wave[i].alive==1) && (wave[i].x<=ENEMY_BORDER || wave[i].x>=SCREEN_WIDTH-ENEMY_BORDER-ENEMY_WIDTH)){
                for (Uint8 j=0 ; j<round.total_enemy ; j++){
                    if (wave[j].type!=FAST){
                        wave[j].y+=ENEMY_DROP ;
                    }
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
            if (wave[i].alive==1 && wave[i].type != FAST){
                wave[i].x+=ENEMY_MOVE* *move_sens ;
            }
        }
    }
}

void update_fast_enemy(Enemy* wave, Round round, short* fast_move_sens, bool* fast_last_move_drop){
    if (!*fast_last_move_drop){
        for (Uint8 i=0 ; i<round.total_enemy ; i++){
            if ((wave[i].type == FAST) && (wave[i].alive==1) && (wave[i].x<=ENEMY_BORDER || wave[i].x>=SCREEN_WIDTH-ENEMY_BORDER-ENEMY_WIDTH)){
                for (Uint8 j=0 ; j<round.total_enemy ; j++){
                    if (wave[j].type==FAST){
                        wave[j].y+=ENEMY_DROP ;
                    }
                }
                *fast_move_sens*=-1 ;
                *fast_last_move_drop = true ;
                break ;
            }
        }
    }
    else{*fast_last_move_drop=false;}
    if (!*fast_last_move_drop){
        for (Uint8 i=0 ; i<round.total_enemy ; i++){
            if (wave[i].alive==1 && wave[i].type == FAST){
                wave[i].x+=ENEMY_MOVE* *fast_move_sens ;
            }
        }
    }
}

void new_bonus(Enemy* bonus_enemy, float* bonus_time, short* bonus_sens){
    bonus_enemy->alive = true ;
    if (rand()%2==0){
        bonus_enemy->x = -bonus_enemy->w ;
        *bonus_sens = 1 ;
    }
    else{
        bonus_enemy->x = SCREEN_WIDTH ;
        *bonus_sens = -1 ;
    }
    *bonus_time = (rand()/(float)(RAND_MAX) * 30) ;
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
