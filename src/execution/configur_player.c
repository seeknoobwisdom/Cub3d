#include "../include/cub3d.h"


void config_player(t_cub3d   *cub3d, t_player *player)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(cub3d->map[i])
    {
        while(cub3d->map[i][j])
        {
            if (cub3d->map[i][j] == 'N'|| cub3d->map[i][j] == 'S' || cub3d->map[i][j] == 'E' || cub3d->map[i][j] == 'W')
            {
                player->position[0] = j +1;
                player->position[1] = i + 1;
                break;
            }
            j++;
        }
        if (cub3d->map[i][j] && (cub3d->map[i][j] == 'N'|| cub3d->map[i][j] == 'S' || cub3d->map[i][j] == 'E' || cub3d->map[i][j] == 'W'))
            break;
        j = 0;
        i++;
    }
    if (cub3d->map[i][j] == 'N')
    {
        player->dir[0] = 0;
        player->dir[1] = -1;
        printf("up\n");
    }
    if (cub3d->map[i][j] == 'W')
    {
        player->dir[0] = -1;
        player->dir[1] = 0;
        printf("left\n");
    }
    if (cub3d->map[i][j] == 'S')
    {
        player->dir[0] = 0;
        player->dir[1] = 1;
        printf("down\n");
    }
    if (cub3d->map[i][j] == 'E')
    {
        player->dir[0] = 1;
        player->dir[1] = 0;
        printf("right\n");
    }
    player->movespeed = 4;
    player->c = cub3d->map[i][j];
    cub3d->map[i][j] = '0';
    cub3d->player.position[0] = cub3d->player.position[0] * SQUARE_SIZE- SQUARE_SIZE/2;
    cub3d->player.position[1] = cub3d->player.position[1] * SQUARE_SIZE- SQUARE_SIZE/2;
    cub3d->player.rotation_speed = 0.2;
    cub3d->player.angle = atan2(-player->dir[1], player->dir[0]);  
}