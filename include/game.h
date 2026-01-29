#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include "entity.h"
#include "enemy.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 20
#define PLAYER_SPEED 400.0f

#define BULLET_WIDTH 5
#define BULLET_HEIGHT 20
#define BULLET_SPEED 600.0f

bool init(SDL_Window **window, SDL_Renderer **renderer);
void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active);
void update_pos(Entity *player, Entity *bullet, bool *bullet_active, Entity* enemy_bullet, Uint8* enemy_bullet_compt, float dt);
void kill_enemy(Entity* bullet, bool* bullet_active, Enemy* wave, Uint8 lignes, Uint8* enemy_compt);
void damage_player(Entity* enemy_bullet, Uint8* enemy_bullet_compt, Entity player, Uint8* lives) ;
void render(SDL_Renderer *renderer, Entity *player, Entity *bullet, Enemy *wave, bool bullet_active, Uint8 lignes, Entity* enemy_bullet, Uint8* enemy_bullet_compt);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif
