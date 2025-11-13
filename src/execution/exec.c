#include "../include/cub3d.h"


// in your cub3d struct


/*
determine the sqaue size 
square size is will be the 
the line width /ft_strlen() = square width
the line hight /numberofstring = square hight 

*/




// need to get re wrote with much understanding

// void    draw_the_map_2d(t_cub3d *cub3d)
// {
//     int x;
//     int y;
//     int curr_x;
//     int curr_y;

//     y = 0;
//     x = 0;
//     while(y < cub3d->mlx.size_y)
//     {
//         while(x < cub3d->mlx.size_x )
//         {
//             curr_y = y/(SQUARE_SIZE);
//             curr_x = x/(SQUARE_SIZE);

//             if (cub3d->map[curr_y][curr_x] && cub3d->map[curr_y][curr_x] == '1')
//                 mlx_pixel_put(cub3d->mlx.mlx,cub3d->mlx.win,x ,y,0xFF0000 );
//             else
//                  mlx_pixel_put(cub3d->mlx.mlx,cub3d->mlx.win,x,y,0xFFFFF );
//             x++;
//         }
//         x = 0;
//         y++;
//     }
// }


// void    config_player(t_cub3d   *cub3d, t_player  *player)
// {

// }

// void    config_map(t_cub3d   *cub3d,t_map  *map)
// {

// }

// void    draw_player_2d(t_cub3d   *cub3d, int d)
// {
//     /*
//     player will be circle with radius the middel will be the point(x, y)
//     */
//    int cx = cub3d->player.position[0]; // the mideel of the square not on the edges
//    int cy = cub3d->player.position[1];
//    int x = cx - RADIUS;
//    while (x <= cx + RADIUS)
//    {
//        int y = cy - RADIUS;
//        while (y <= cy + RADIUS)
//        {
//            int dx = x - cx;  // distance from center in x
//            int dy = y - cy;  // distance from center in y
   
//            if (squr(dx) + squr(dy) <= squr(RADIUS))
//            {
//                mlx_pixel_put(cub3d->mlx.mlx, cub3d->mlx.win, x,  y , 0xFFFFFF);
//            }
//            y++;
//        }
//        x++;
//    }
//    draw_dirction(cub3d, d);
// }




// void    draw_line(t_cub3d *cub3d, int x, int y, int x2, int y2)
// {
//     int dx = x2 - x;
//     int dy = y2 - y;

//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

//     float step_x = dx / (float)steps;
//     float step_y = dy / (float)steps;
//     int  curr_x;
//     int  curr_y;
//     float xf = x;
//     float yf = y;

//     for (int i = 0; i <= steps; i++)
//     {
//         curr_x = xf/(SQUARE_SIZE);
//         curr_y = yf/(SQUARE_SIZE);
//         if (x>= 0 && y>=0 &&curr_x >= 0 &&curr_y>= 0 && cub3d->map[curr_y][curr_x] == '0')
//         {
//             mlx_pixel_put(cub3d->mlx.mlx, cub3d->mlx.win, (int)xf, (int)yf, 0xF000F0);
//         }
//         else
//             break;
//         xf += step_x;
//         yf += step_y;
//     }
// }







// void    return_current_area(t_cub3d   *cub3d)
// {
//     /*
//     player will be circle with radius the middel will be the point(x, y)
//     */
//    int cx = cub3d->player.position[0]; // the mideel of the square not on the edges
//    int cy = cub3d->player.position[1];
//     int curr_y ;
//     int    curr_x ;
//    int x = cx - ARROW_LEN - ARROW_LEN/ 2;
//    while (x <= cx + ARROW_LEN+ARROW_LEN/ 2  && cub3d->mlx.size_x > x)
//    {
//        int y = cy - ARROW_LEN- ARROW_LEN/ 2;
//        while (y <= cy + ARROW_LEN+ ARROW_LEN/ 2 && cub3d->mlx.size_y > y)
//        {
//            int dx = x - cx;  // distance from center in x
//            int dy = y - cy;  // distance from center in y
//             curr_x = x/(SQUARE_SIZE);
//             curr_y = y/(SQUARE_SIZE);
//            if (y > 0 && x > 0 && squr(dx) + squr(dy) <= squr(ARROW_LEN + 30))
//            {
//             if (curr_x >= 0 &&curr_y>= 0 &&cub3d->map[curr_y][curr_x] && cub3d->map[curr_y][curr_x] == '1')
//                 mlx_pixel_put(cub3d->mlx.mlx,cub3d->mlx.win,x ,y,0xFF0000 );
//             else
//                  mlx_pixel_put(cub3d->mlx.mlx,cub3d->mlx.win,x,y,0xFFFFF );
//            }
//            y++;
//        }
//        x++;
//    }
// }

// void    draw_dirction(t_cub3d   *cub3d, int d)
// {
//     int arrow_x;
//     int arrow_y;

//     if (cub3d->player.c == 'N' && d == 0)
//     {
//         cub3d->player.angle = 90 * (M_PI/ 180);
//         printf("up\n");
//     }
//     if (cub3d->player.c == 'W'&& d == 0)
//     {
//         cub3d->player.angle = 180 * (M_PI/ 180);
//         printf("left\n");
//     }
//     if (cub3d->player.c == 'S'&& d == 0)
//     {
//         cub3d->player.angle = 270 * (M_PI/ 180);
//         printf("down\n");
//     }
//     if (cub3d->player.c == 'E'&& d == 0)
//     {
//         cub3d->player.angle = 0 * (M_PI/ 180);
//         printf("right\n");
//     }
//     cub3d->player.fov_angle = -60 *M_PI/180; 
//     while( cub3d->player.fov_angle < 60 *M_PI/180 )
//     {
//         arrow_x = cub3d->player.position[0]+ (RADIUS + ARROW_LEN) * cosf(cub3d->player.fov_angle +cub3d->player.angle);
//         arrow_y = cub3d->player.position[1]-(RADIUS + ARROW_LEN) * sinf(cub3d->player.fov_angle+cub3d->player.angle);
//         draw_line(cub3d,cub3d->player.position[0], cub3d->player.position[1], arrow_x, arrow_y);
//         cub3d->player.fov_angle *= 180/M_PI;
//           cub3d->player.fov_angle += RES;
//         cub3d->player.fov_angle *= M_PI/180;  
//     }
// }

int hundle_exit(t_cub3d   *cub3d)
{
        ahasna(cub3d); // important for the freeing 
        printf ("exit in clean way after freeing\n");
        exit(0);
}

void    main_execution(t_cub3d   *cub3d)
{
    config_mlx(cub3d);
    cub3d->mlx.mlx = mlx_init();
    cub3d->mlx.win = mlx_new_window(cub3d->mlx.mlx, cub3d->mlx.size_x, cub3d->mlx.size_y, "CUB3D");
        cub3d->img.img = mlx_new_image(cub3d->mlx.mlx, cub3d->mlx.size_x, cub3d->mlx.size_y);
    cub3d->img.addr = mlx_get_data_addr(cub3d->img.img,
    &cub3d->img.bpp, &cub3d->img.line_length, &cub3d->img.endian);
    cub3d->img.width = cub3d->mlx.size_x;
    cub3d->img.height = cub3d->mlx.size_y;
    load_texture(cub3d, 0, cub3d->no);
    load_texture(cub3d, 1, cub3d->so);
    load_texture(cub3d, 2, cub3d->ea);
    load_texture(cub3d, 3, cub3d->we);

    // draw_the_map_2d(cub3d);
    // config_map(&map, cub3d);
    config_player(cub3d, &cub3d->player);
    mlx_key_hook(cub3d->mlx.win,keys_pressed, (void *)cub3d);
    // draw_player_2d(cub3d, 0);
    mlx_loop_hook(cub3d->mlx.mlx, game_loop, cub3d);
    mlx_hook(cub3d->mlx.win, 17, 0 ,hundle_exit, cub3d );
    mlx_loop(cub3d->mlx.mlx);

    // ahasna(cub3d); // important for the freeing 
}