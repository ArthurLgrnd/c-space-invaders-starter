#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entity.h"
#include "game.h"
#include "enemy.h"
    
int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!init(&window, &renderer))
    {
        return 1;
    }

    bool running = true;
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
    float move_time = 0.5 ;
    short move_sens = 1 ;
    bool last_move_drop = true ;

    Uint8 lignes = 3 ;
    Enemy* wave = malloc (sizeof(Enemy)*lignes*ENEMY_NUMBER) ;

    new_wave(wave, lignes) ;

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
        update_pos(&player, &bullet, &bullet_active, dt);
        if (bullet_active){
            kill_enemy(&bullet, &bullet_active, wave, lignes);
        }
        if ((ticks - last_move)/1000.0f > move_time){
            last_move+= move_time*1000.0f ;
            update_enemy(wave, lignes, &move_sens, &last_move_drop) ;
        }   
        render(renderer, &player, &bullet, wave, bullet_active, lignes);
    }

    cleanup(window, renderer);
    return 0;
}
