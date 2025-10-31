#include "../include/cub3d.h"

int game_loop(void *param)
{
    t_cub3d *cub3d = (t_cub3d *)param;
    render_scene(cub3d);
    return (0);
}
// In main:


int    check_area(int   test_x,int  test_y,t_cub3d * cub3d)
{
   int cx = test_x; // the mideel of the square not on the edges
   int cy = test_y;
    int  curr_x = cub3d->player.position[0];
   int  curr_y = cub3d->player.position[1];
   int x = cx - RADIUS;
   while (x <= cx + RADIUS)
   {
       int y = cy - RADIUS;
       while (y <= cy + RADIUS)
       {
            curr_y = y/(SQUARE_SIZE);
            curr_x = x/(SQUARE_SIZE);
           int dx = x - cx;  // distance from center in x
           int dy = y - cy;  // distance from center in y
   
           if (squr(dx) + squr(dy) <= squr(RADIUS) && cub3d->map[curr_y][curr_x] == '1')
           {
               return(1);
           }
           y++;
       }
       x++;
   }
   return (0);
}


int keys_pressed(int keycode, void *param)
{
    t_cub3d *cub3d = (t_cub3d *)param;
    int test_x;
    int test_y;

    if (keycode == 65307 ) // ESC on Linux (X11)
    {
        mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
    
        ahasna(cub3d);
        exit(0);
    }
    if (keycode == 65363) // Left arrow
    {
        // return_current_area(cub3d);
        printf("left\n");

        cub3d->player.angle += cub3d->player.rotation_speed;
        // draw_player_2d(cub3d, 1);
    }
    if (keycode ==65361 ) // Right arrow
    {
        //  return_current_area(cub3d);
        printf("right\n");
        cub3d->player.angle -= cub3d->player.rotation_speed;
        // draw_player_2d(cub3d, 1);
    }
    if (keycode ==65362 )
    {
        // return_current_area(cub3d);
        test_x =cub3d->player.position[0] + cub3d->player.movespeed *cosf(cub3d->player.angle);
        test_y = cub3d->player.position[1] - cub3d->player.movespeed * sinf(cub3d->player.angle);
        if (check_area(test_x, test_y, cub3d) == 0)
        {
            cub3d->player.position[0] = test_x;
            cub3d->player.position[1] = test_y;
        }
        // draw_player_2d(cub3d, 1);
        printf("forward\n");

    }
    if (keycode ==65364)
    {
        // return_current_area(cub3d);
        test_x =cub3d->player.position[0] - cub3d->player.movespeed *cosf(cub3d->player.angle);
        test_y = cub3d->player.position[1] + cub3d->player.movespeed * sinf(cub3d->player.angle);
        if (check_area(test_x, test_y, cub3d) == 0)
        {
            cub3d->player.position[0] = test_x;
            cub3d->player.position[1] = test_y;
        }
        // draw_player_2d(cub3d, 1);
        printf("backword\n");
    }
    if (cub3d->player.angle < 0)
        cub3d->player.angle += 2 * M_PI;
    if (cub3d->player.angle > 2 * M_PI)
        cub3d->player.angle -= 2 * M_PI;
    return (0);
}