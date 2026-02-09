#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "entity.h"
#include "game.h"
#include "enemy.h"
#include "video.h"
    
int main(void){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!init(&window, &renderer))
    {
        return 1;
    }
    SDL_Texture* heart = init_image(renderer, "./images/coeur.png") ;
    SDL_Texture* invaders[9] = {NULL} ;
    init_invaders(invaders, renderer) ;
    SDL_Texture* png_player = init_image(renderer, "./images/player.png") ;
    SDL_Texture* mushroom = init_image(renderer, "./images/mushroom.png") ;

    TTF_Font* micro5= TTF_OpenFont("./Micro5-Regular.ttf", 80) ;

    srand(time(NULL)) ;

    bool running = true;
    bool win = false ;
    Uint8 lives = 3 ;
    Uint32 score = 0 ;
    Uint32 last_ticks = SDL_GetTicks();

    Entity player = {
        .x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
        .y = SCREEN_HEIGHT - 60,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
        .vx = 0,
        .vy = 0};

    Entity bullet = {0};

    bool bullet_active = false;
    Uint32 last_move = last_ticks ;
    Uint32 last_half_move = last_ticks ; /*temps pour les mouvements supplémentaires des ennemis FAST et les mouvements NINJA*/
    float round_move_time = 1 ; /*Temps entre chaque déplacement d'ennemis qui évolue avec les nouveau round*/  
    float var_move_time = round_move_time ; /*Temps entre chaque déplacement d'ennemis qui évolue au sein du d'un round*/
    short move_sens = 1 ;
    bool last_move_drop = true ;

    Round round = {0, 2*ENEMY_NUMBER} ;
    Enemy* wave = malloc (sizeof(Enemy)*4*ENEMY_NUMBER) ;
    Uint8 enemy_compt = 0 ;

    Uint8 enemy_bullet_compt = 0 ;
    Enemy_bullet* enemy_bullet = malloc(sizeof(Enemy_bullet)*2);
    Uint8 enemy_bullet_max = 2 ; /*maximum de tirs ennemis stockables pour le moment*/
    float enemy_bullet_time = 0.8 ; /*Temps moyen entre chaque tir ennemi*/
    float var_enemy_bullet_time = (rand()/(float)(RAND_MAX) * 2 * enemy_bullet_time) ;
    printf("%f", var_enemy_bullet_time);
    Uint32 last_bullet = last_ticks ;

    new_wave(wave, &round, &enemy_compt, &round_move_time, &var_move_time) ;

    while (running)
    {
        Uint32 ticks = SDL_GetTicks();
        float dt = (ticks - last_ticks) / 1000.0f;
        if (dt > 0.05f)
            dt = 0.05f;
        last_ticks = ticks;

        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        handle_input(&running, keys, &player, &bullet, &bullet_active);

        update_pos(&player, &bullet, &bullet_active, enemy_bullet, &enemy_bullet_compt, dt);

        if (bullet_active){
            kill_enemy(&bullet, &bullet_active, wave, round, &enemy_compt, &score);
        }

        damage_player(enemy_bullet, &enemy_bullet_compt, player, &lives) ;

        if ((ticks - last_move)/1000.0f > var_move_time){
            last_move+= var_move_time*1000.0f ;
            last_half_move = last_move ;
            update_enemy(wave, round, &move_sens, &last_move_drop, &var_move_time) ;
        }
        else if ((ticks - last_half_move)/1000.0f > var_move_time/2.0f){
            last_half_move+=var_move_time*500.0f +1 ; /*+1 pour être certain de ne pas avoir deux mouvements fast avant un classique en cas de mauvais arrondis*/
            update_fast_enemy(wave, round, move_sens);
            ninja_dash(wave, round, enemy_compt) ;
        }

        if ((ticks-last_bullet)/1000.0f > var_enemy_bullet_time){
            last_bullet+=var_enemy_bullet_time*1000.0f;
            var_enemy_bullet_time = (rand()/(float)(RAND_MAX) * 2 * enemy_bullet_time) * (2-(float)(enemy_compt)/round.total_enemy) ; /*Augementation du temps entre chaque shoot quand le nombre d'ennemis diminue pour éviter que les derniers ennemis tirent trop fréquemment*/
            if(!new_enemy_bullet(wave, enemy_compt, &enemy_bullet_compt, &enemy_bullet_max, &enemy_bullet, round)){
                break ;
            }
        }
        render(renderer, &player, &bullet, wave, bullet_active, round, enemy_bullet, &enemy_bullet_compt, heart, lives, invaders, png_player, mushroom, micro5, score);
        
        if (lives <= 0){
           win = false ;
           break ;
        }
        if (enemy_compt <= 0){
            new_wave(wave, &round, &enemy_compt, &round_move_time, &var_move_time) ;
            move_sens = 1 ;
            last_move_drop = true;
            enemy_bullet_compt = 0;
            render(renderer, &player, &bullet, wave, bullet_active, round, enemy_bullet, &enemy_bullet_compt, heart, lives, invaders, png_player, mushroom, micro5, score);
            while(last_ticks+1000>SDL_GetTicks()){}
            last_ticks = SDL_GetTicks();
            last_move = last_ticks ;
            last_half_move = last_ticks ;
            last_bullet = last_ticks ;
        }
        
        if (enemy_down(wave,round)){
            win = false ;
            break ;
        }
    }

    if (win) printf("vous avez gagné \n") ;
    else printf("vous avez perdu \n") ;
    free(wave);
    free(enemy_bullet);
    SDL_DestroyTexture(heart);
    SDL_DestroyTexture(png_player);
    SDL_DestroyTexture(mushroom);
    for (Uint8 i=0 ; i<9 ; i++){
        SDL_DestroyTexture(invaders[i]) ;
    }
    cleanup(window, renderer);
    return 0;
}
