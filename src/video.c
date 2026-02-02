#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.h"
#include "enemy.h"
#include "game.h"
#include "video.h"


bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
        return false;
    } 
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        SDL_Log("Erreur IMG_Init: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *window = SDL_CreateWindow("Space Invaders (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!*window){
        SDL_Log("Erreur SDL_CreateWindow: %s", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer){
        SDL_Log("Erreur SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

SDL_Texture* init_image(SDL_Renderer* renderer, char* src_img){
    SDL_Texture* image = IMG_LoadTexture(renderer, src_img) ;
    if (image==NULL){printf("Erreur init_image %s \n", src_img);}
    return image ;
}

void init_invaders(SDL_Texture** invaders, SDL_Renderer* renderer){
    invaders[0]=init_image(renderer, "./images/invaders_classic.png");
    invaders[1]=init_image(renderer, "./images/invaders_shield.png");
    invaders[2]=init_image(renderer, "./images/invaders_br_shield.png");
    invaders[3]=init_image(renderer, "./images/invaders_no_shield.png");
    invaders[4]=init_image(renderer, "./images/invaders_ninja.png");
    invaders[5]=init_image(renderer, "./images/invaders_fast.png");
    invaders[6]=init_image(renderer, "./images/invaders_fast_shoot.png");
    invaders[7]=init_image(renderer, "./images/invaders_military.png");
    invaders[8]=init_image(renderer, "./images/invaders_healer.png");
}

void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, Enemy *wave, bool bullet_active, Uint8 lignes, Entity* enemy_bullet, Uint8* enemy_bullet_compt, SDL_Texture* heart, Uint8 lives, SDL_Texture* invaders, SDL_Texture* png_player)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect hud = {3,3,SCREEN_WIDTH-6,60};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &hud);

    SDL_Rect player_rect = {
        (int)player->x, (int)player->y,
        player->w, player->h};
    SDL_RenderCopy(renderer, png_player, NULL, &player_rect);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) ;
    for (int i=0 ; i<lignes*ENEMY_NUMBER ; i++){
        if (wave[i].alive){
        SDL_Rect enemy_rect = {
            (int)wave[i].x, (int)wave[i].y,
            wave[i].w, wave[i].h} ;
        SDL_RenderCopy(renderer, invaders, NULL ,&enemy_rect) ;
        }
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
    for (int i=0 ; i<lives ; i++){
    SDL_Rect heart_size = {500 + i*60, 10, 50, 50};
    SDL_RenderCopy(renderer,heart,NULL,&heart_size);
    }
    SDL_RenderPresent(renderer);
}


void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
