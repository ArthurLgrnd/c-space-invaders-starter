#ifndef GAME_H
#define GAME_H


#include <stdbool.h>
#include <SDL2/SDL.h>
#include "entity.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 35
#define PLAYER_SPEED 400.0f

#define BULLET_WIDTH 5
#define BULLET_HEIGHT 20
#define BULLET_SPEED 600.0f

typedef struct {
    Uint8 number, total_enemy ;
} Round ;

#include "enemy.h"

void handle_input(bool *running, const Uint8 *keys, Entity *player, Entity *bullet, bool *bullet_active);
void update_pos(Entity *player, Entity *bullet, bool *bullet_active, Enemy_bullet* enemy_bullet, Uint8* enemy_bullet_compt, float dt);
void kill_enemy(Entity* bullet, bool* bullet_active, Enemy* wave, Round round, Uint8* enemy_compt, Uint32* score);
void damage_player(Enemy_bullet* enemy_bullet, Uint8* enemy_bullet_compt, Entity player, Uint8* lives) ;


#endif
