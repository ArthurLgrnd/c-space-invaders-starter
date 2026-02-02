#ifndef VIDEO_H
#define VIDEO_H


#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.h"
#include "enemy.h"

bool init(SDL_Window **window, SDL_Renderer **renderer);
SDL_Texture* init_image(SDL_Renderer* renderer, char* src_img);
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, Enemy *wave, bool bullet_active, Uint8 lignes, Entity* enemy_bullet, Uint8* enemy_bullet_compt, SDL_Texture* heart, Uint8 lives, SDL_Texture* invaders, SDL_Texture* png_player);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif