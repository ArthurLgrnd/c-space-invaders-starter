#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "enemy.h"
#include "entity.h"
#include <stdio.h>
#include <stdlib.h>



bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Space Invaders (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!*window)
    {
        SDL_Log("Erreur SDL_CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer)
    {
        SDL_Log("Erreur SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}

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


void update_pos(Entity *player, Entity *bullet, bool *bullet_active, Entity* enemy_bullet, Uint8* enemy_bullet_compt, float dt)
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

void kill_enemy(Entity *bullet, bool *bullet_active, Enemy *wave, Uint8 lignes, Uint8* enemy_compt){
    for (Uint8 i=0 ; i<lignes*ENEMY_NUMBER ; i++){
        if ((((wave[i].y <= bullet->y) && (bullet->y <= wave[i].y + wave[i].h)) || ((wave[i].y <= bullet->y + bullet->h) && (bullet->y + bullet->h <= wave[i].y + wave[i].h)) ) && (((wave[i].x <= bullet->x) && (bullet->x <= wave[i].x + wave[i].w)) || ((wave[i].x <= bullet->x + bullet->w) && (bullet->x + bullet->w <= wave[i].x + wave[i].w)) ) ){
            wave[i].x = -10-ENEMY_WIDTH ;
            wave[i].alive = false ;
            *bullet_active = false ;
            *enemy_compt-=1 ;
            break ;
        }
    }
}

void damage_player(Entity* enemy_bullet, Uint8* enemy_bullet_compt, Entity player, Uint8* lives){
    for (Uint8 i=0 ; i<*enemy_bullet_compt ; i++){
        if ((((player.y <= enemy_bullet[i].y) && (enemy_bullet[i].y <= player.y + player.h)) || ((player.y <= enemy_bullet[i].y + enemy_bullet[i].h) && (enemy_bullet[i].y + enemy_bullet[i].h <= player.y + player.h)) ) && (((player.x <= enemy_bullet[i].x) && (enemy_bullet[i].x <= player.x + player.w)) || ((player.x <= enemy_bullet[i].x + enemy_bullet[i].w) && (enemy_bullet[i].x + enemy_bullet[i].w <= player.x + player.w)) ) ){
            *lives -= 1 ;
            *enemy_bullet_compt -= 1;
            for (int j = i ; j<*enemy_bullet_compt ; j++){
                enemy_bullet[j]=enemy_bullet[j+1] ;
            }
            i-=1 ;
        }
    }
}



void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, Enemy *wave, bool bullet_active, Uint8 lignes, Entity* enemy_bullet, Uint8* enemy_bullet_compt, SDL_Surface* heart)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect player_rect = {
        (int)player->x, (int)player->y,
        player->w, player->h};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &player_rect);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) ;
    for (int i=0 ; i<lignes*ENEMY_NUMBER ; i++){
        SDL_Rect enemy_rect = {
            (int)wave[i].x, (int)wave[i].y,
            wave[i].w, wave[i].h} ;
        SDL_RenderFillRect(renderer, &enemy_rect) ;
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) ;
    }

    if (bullet_active)
    {
        SDL_Rect bullet_rect = {
            (int)bullet->x, (int)bullet->y,
            bullet->w, bullet->h};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &bullet_rect);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int i=0 ; i<*enemy_bullet_compt ; i++){
        SDL_Rect enemy_bullet_rect = {
            (int)enemy_bullet[i].x, (int)enemy_bullet[i].y,
            enemy_bullet[i].w, enemy_bullet[i].h};
        SDL_RenderFillRect(renderer, &enemy_bullet_rect);
    }
    SDL_Texture* heart1=SDL_CreateTextureFromSurface(renderer,heart);
    SDL_Rect rect = {50,10,50,50};
    SDL_RenderCopy(renderer,heart1,NULL,&rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(heart1) ;
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
