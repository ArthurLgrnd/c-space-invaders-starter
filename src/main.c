#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
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

    bool running = true;
    bool win = false ;
    Uint8 lives = 5 ;
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
    float move_time = 1 ;
    short move_sens = 1 ;
    bool last_move_drop = true ;

    Uint8 lignes = 3 ;
    Enemy* wave = malloc (sizeof(Enemy)*lignes*ENEMY_NUMBER) ;
    Uint8 enemy_compt = 0 ;

    Uint8 enemy_bullet_compt = 0 ;
    Enemy_bullet* enemy_bullet = malloc(sizeof(Enemy_bullet)*2);
    Uint8 enemy_bullet_max = 2 ; // maximum de tirs ennemis stockables pour le moment
    float enemy_bullet_time = 0.8 ;
    Uint32 last_bullet = last_ticks ;

    new_wave(wave, lignes, &enemy_compt) ;

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
            kill_enemy(&bullet, &bullet_active, wave, lignes, &enemy_compt);
        }

        damage_player(enemy_bullet, &enemy_bullet_compt, player, &lives) ;

        if ((ticks - last_move)/1000.0f > move_time){
            last_move+= move_time*1000.0f ;
            last_half_move = last_move ;
            update_enemy(wave, lignes, &move_sens, &last_move_drop, &move_time) ;
        }
        else if ((ticks - last_half_move)/1000.0f > move_time/2.0f){
            last_half_move+=move_time*500.0f +1 ; /*+1 pour être certain de ne pas avoir deux mouvements fast avant un classique en cas de mauvais arrondis*/
            update_fast_enemy(wave, lignes, move_sens);
            ninja_dash(wave, lignes, enemy_compt) ;
        }

        if ((ticks-last_bullet)/1000.0f > enemy_bullet_time){
            last_bullet+=enemy_bullet_time*1000.0f;
            if(!new_enemy_bullet(wave, enemy_compt, &enemy_bullet_compt, &enemy_bullet_max, &enemy_bullet, lignes)){
                break ;
            }
        }
        render(renderer, &player, &bullet, wave, bullet_active, lignes, enemy_bullet, &enemy_bullet_compt, heart, lives, invaders, png_player, mushroom);
        
        if (lives <= 0){
           win = false ;
           break ;
        }
        if (enemy_compt <= 0){
            win = true ; 
            break ;
        }
        
        if (enemy_down(wave,lignes)){
            win = false ;
            break ;
        }
    }

    if (win) printf("vous avez gagné \n") ;
    else printf("vous avez perdu \n") ;
    free(wave);
    free(enemy_bullet);
    SDL_DestroyTexture(heart);
    cleanup(window, renderer);
    return 0;
}
