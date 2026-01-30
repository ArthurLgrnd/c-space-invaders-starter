#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_NUMBER 10 
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 20
#define ENEMY_MOVE 20
#define ENEMY_BORDER 20
#define ENEMY_DROP 20 //distance descendue par cran

#define ENEMY_BULLET_WIDTH 5
#define ENEMY_BULLET_HEIGHT 20
#define ENEMY_BULLET_SPEED 600.0f

typedef struct
{
    float x, y;
    int w, h;
    bool alive;
} Enemy;

void new_wave(Enemy* wave, Uint8 lignes, Uint8* enemy_number) ;
void new_enemy_bullet(Enemy* wave, Uint8 enemy_compt, Uint8* enemy_bullet_compt, Entity* enemy_bullet, Uint8* enemy_bullet_max);
void update_enemy(Enemy* wave, Uint8 lignes, short* move_sens, bool* last_move_drop) ;
bool enemy_down(Enemy* wave, Uint8 lignes) ;



#endif