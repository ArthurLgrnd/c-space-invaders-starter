#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
    if(TTF_Init()!=0){
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    *window = SDL_CreateWindow("Space Invaders (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!*window){
        SDL_Log("Erreur SDL_CreateWindow: %s", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer){
        SDL_Log("Erreur SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        TTF_Quit();
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

void draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, char* text, int x, int y){
    SDL_Surface* surface =  TTF_RenderText_Solid(font, text, color) ;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect size = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer,texture,NULL,&size);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, Enemy *wave, bool bullet_active, Round round, Enemy_bullet* enemy_bullet, Uint8* enemy_bullet_compt, SDL_Texture* heart, Uint8 lives, SDL_Texture** invaders, SDL_Texture* png_player, SDL_Texture* mushroom, TTF_Font* micro5, Uint32 score)
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
    for (int i=0 ; i<round.lignes*ENEMY_NUMBER ; i++){
        if (wave[i].alive){
            SDL_Rect enemy_rect = {
                (int)wave[i].x, (int)wave[i].y,
                wave[i].w, wave[i].h} ;
            SDL_RenderCopy(renderer, invaders[wave[i].type], NULL ,&enemy_rect) ;
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
        if (enemy_bullet[i].mushroom){
            SDL_RenderCopy(renderer, mushroom, NULL, &enemy_bullet_rect);
        }
        else{
            SDL_RenderFillRect(renderer, &enemy_bullet_rect);
        }
    }
    if (lives<6){
        for (int i=0 ; i<lives ; i++){
        SDL_Rect heart_size = {500 + i*60, 10, 50, 50};
        SDL_RenderCopy(renderer,heart,NULL,&heart_size);
        }
    }
    else{
        SDL_Rect heart_size = {560, 10, 50, 50};
        SDL_RenderCopy(renderer,heart,NULL,&heart_size);
        SDL_Color rouge = {255,0,0,255} ;
        char text_lives[10] ;
        snprintf(text_lives, sizeof(text_lives), "x%d", lives);
        draw_text(renderer, micro5, rouge, text_lives, 620, -8) ;
    }
    SDL_Color blanc = {255,255,255,255} ;
    char text_score[10];
    snprintf(text_score,sizeof(text_score), "%05d", score);
    draw_text(renderer, micro5, blanc, text_score, 50, -8);
    SDL_RenderPresent(renderer);
}


void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    TTF_Quit();    
    IMG_Quit();
    SDL_Quit();
}
