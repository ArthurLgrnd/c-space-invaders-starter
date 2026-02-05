#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "enemy.h"
#include "entity.h"


void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *running = false;
    }

    player->vx = 0.0f;
    if (keys[SDL_SCANCODE_LEFT])
        player->vx = -PLAYER_SPEED;
    if (keys[SDL_SCANCODE_RIGHT])
        player->vx = PLAYER_SPEED;

    if (keys[SDL_SCANCODE_SPACE] && !*bullet_active)
    {
        *bullet_active = true;
        bullet->x = player->x + player->w / 2 - BULLET_WIDTH / 2;
        bullet->y = player->y;
        bullet->w = BULLET_WIDTH;
        bullet->h = BULLET_HEIGHT;
        bullet->vy = -BULLET_SPEED;
    }
}


void update_pos(Entity *player, Entity *bullet, bool *bullet_active, Enemy_bullet* enemy_bullet, Uint8* enemy_bullet_compt, float dt)
{
    player->x += player->vx * dt;

    if (player->x < 0)
        player->x = 0;
    if (player->x + player->w > SCREEN_WIDTH)
        player->x = SCREEN_WIDTH - player->w;

    if (*bullet_active){
        bullet->y += bullet->vy * dt;
        if (bullet->y + bullet->h < 0)
            *bullet_active = false;
    }
    for (int i=0 ; i<*enemy_bullet_compt ; i++){
        enemy_bullet[i].y += enemy_bullet[i].vy * dt ;
        if (enemy_bullet[i].y>SCREEN_HEIGHT){
            *enemy_bullet_compt-=1;
            for (int j = i ; j<*enemy_bullet_compt ; j++){
                enemy_bullet[j]=enemy_bullet[j+1] ;
            }
            i-=1 ;
        }
    }
}

void kill_enemy(Entity *bullet, bool *bullet_active, Enemy *wave, Round round, Uint8* enemy_compt, Uint32* score){
    for (Uint8 i=0 ; i<round.lignes*ENEMY_NUMBER ; i++){
        if ((((wave[i].y <= bullet->y) && (bullet->y <= wave[i].y + wave[i].h)) || ((wave[i].y <= bullet->y + bullet->h) && (bullet->y + bullet->h <= wave[i].y + wave[i].h)) ) && (((wave[i].x <= bullet->x) && (bullet->x <= wave[i].x + wave[i].w)) || ((wave[i].x <= bullet->x + bullet->w) && (bullet->x + bullet->w <= wave[i].x + wave[i].w)) ) ){
            if (wave[i].type == SHIELD){
                wave[i].type = BR_SHIELD ;
            }
            else if (wave[i].type == BR_SHIELD){
                wave[i].type = NO_SHIELD ;
            }
            else{
                wave[i].x = -10-ENEMY_WIDTH ;
                wave[i].alive = false ;
                *enemy_compt-=1 ;
                if (wave[i].type == NINJA){*score+=50;}
                else if (wave[i].type == CLASSIC || wave[i].type == HEALER){*score+=10;}
                else{*score+=30;}
            }
            *bullet_active = false ;
            break ;
        }
    }
}

void damage_player(Enemy_bullet* enemy_bullet, Uint8* enemy_bullet_compt, Entity player, Uint8* lives){
    for (Uint8 i=0 ; i<*enemy_bullet_compt ; i++){
        if ((((player.y <= enemy_bullet[i].y) && (enemy_bullet[i].y <= player.y + player.h)) || ((player.y <= enemy_bullet[i].y + enemy_bullet[i].h) && (enemy_bullet[i].y + enemy_bullet[i].h <= player.y + player.h)) ) && (((player.x <= enemy_bullet[i].x) && (enemy_bullet[i].x <= player.x + player.w)) || ((player.x <= enemy_bullet[i].x + enemy_bullet[i].w) && (enemy_bullet[i].x + enemy_bullet[i].w <= player.x + player.w)) ) ){
            if (enemy_bullet[i].mushroom){
                *lives += 1 ;
            }
            else{
                *lives -= 1 ;
            }
            *enemy_bullet_compt -= 1;
            for (int j = i ; j<*enemy_bullet_compt ; j++){
                enemy_bullet[j]=enemy_bullet[j+1] ;
            }
            i-=1 ;
        }
    }
}


