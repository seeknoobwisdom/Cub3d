#include "../include/cub3d.h"


// in your cub3d struct

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

/*
determine the sqaue size 
square size is will be the 
the line width /ft_strlen() = square width
the line hight /numberofstring = square hight 

*/




// need to get re wrote with much understanding
double  cast_ray(t_cub3d    *cub3d, double  ray_angle)
{
    double  ray_x = cub3d->player.position[0] / SQUARE_SIZE;;
    double ray_y = cub3d->player.position[1] / SQUARE_SIZE;

    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = -sin(ray_angle);

    int map_x = (int)ray_x;
    int map_y = (int)ray_y;

    double delta_dist_x = fabs(1 / ray_dir_x);// the exact steps to stay on to stay on the same ditr
    double delta_dist_y = fabs(1 / ray_dir_y);

    int step_x, step_y;
    double side_dist_x, side_dist_y;
    if (ray_dir_x < 0)
    {
    step_x = -1;
    side_dist_x = (ray_x - map_x) * delta_dist_x;
    }
    else
    {
    step_x = 1;
    side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;
    }

    if (ray_dir_y < 0)
    {
    step_y = -1;
    side_dist_y = (ray_y - map_y) * delta_dist_y;
    }
    else
    {
    step_y = 1;
    side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y;
    }
    
    int hit = 0;
    int side; // 0 = vertical, 1 = horizontal

    while (hit == 0)
    {
    if (side_dist_x < side_dist_y)
    {
        side_dist_x += delta_dist_x;
        map_x += step_x;
        side = 0;
    }
    else
    {
        side_dist_y += delta_dist_y;
        map_y += step_y;
        side = 1;
    }

    if (cub3d->map[map_y][map_x] == '1')
        hit = 1;
    }
    double perp_wall_dist;
    if (side == 0)
        perp_wall_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x;
    else
        perp_wall_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y;

    return (perp_wall_dist * SQUARE_SIZE);
}

double  cast_ray_side(t_cub3d    *cub3d, double  ray_angle)
{
    double  ray_x = cub3d->player.position[0] / SQUARE_SIZE;;
    double ray_y = cub3d->player.position[1] / SQUARE_SIZE;

    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = -sin(ray_angle);

    int map_x = (int)ray_x;
    int map_y = (int)ray_y;

    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);

    int step_x, step_y;
    double side_dist_x, side_dist_y;
    if (ray_dir_x < 0)
    {
    step_x = -1;
    side_dist_x = (ray_x - map_x) * delta_dist_x;
    }
    else
    {
    step_x = 1;
    side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;
    }

    if (ray_dir_y < 0)
    {
    step_y = -1;
    side_dist_y = (ray_y - map_y) * delta_dist_y;
    }
    else
    {
    step_y = 1;
    side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y;
    }
    
    int hit = 0;
    int side; // 0 = vertical, 1 = horizontal

    while (hit == 0)
    {
    if (side_dist_x < side_dist_y)
    {
        side_dist_x += delta_dist_x;
        map_x += step_x;
        side = 0;
    }
    else
    {
        side_dist_y += delta_dist_y;
        map_y += step_y;
        side = 1;
    }

    if (cub3d->map[map_y][map_x] == '1')
        hit = 1;
    }

    return (side);
}
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

void img_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}


void    config_mlx(t_cub3d   *cub3d)
{
    int x = 0;
    int y = 0;
    (void)cub3d;

    while(cub3d->map[y])
        y++;
    cub3d->mlx.size_y = y * SQUARE_SIZE;
    x = ft_strlen(cub3d->map[0]);
    cub3d->mlx.size_x = x * SQUARE_SIZE;


}

int squr(int num)
{
    return(num * num);
}
int abs(int i)
{
    if (i < 0)
        i = i * -1;
    return(i);
}

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

void draw_vertical_line(t_cub3d *cub3d, int x, int start, int end, int color)
{
    if (start < 0)
        start = 0;
    if (end >= cub3d->mlx.size_y)
        end = cub3d->mlx.size_y - 1;

    for (int y = start; y <= end; y++)
        img_pixel_put(&cub3d->img, x, y, color);
}




void    load_texture(t_cub3d *cub3d, int id, char *path)
{
    cub3d->textures[id].img = mlx_xpm_file_to_image(cub3d->mlx.mlx,
            path, &cub3d->textures[id].width, &cub3d->textures[id].height);
    if (!cub3d->textures[id].img)
    {
        printf("Error: failed to load texture %s\n", path);
        exit(1);
    }
    cub3d->textures[id].addr = mlx_get_data_addr(cub3d->textures[id].img,
            &cub3d->textures[id].bpp,
            &cub3d->textures[id].line_length,
            &cub3d->textures[id].endian);
}



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

int get_tex_pixel(t_texture *tex, int x, int y)
{
    char    *dst;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0); // safety check

    dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
    return (*(unsigned int*)dst);
}

void render_scene(t_cub3d *cub3d)
{
    // Clear image (black)
    ft_memset(cub3d->img.addr, 0, cub3d->img.line_length * cub3d->img.height);

    for (int x = 0; x < cub3d->mlx.size_x; x++)
    {
        // Map x to camera space (-1 to 1)
        double camera_x = 2 * x / (double)cub3d->mlx.size_x - 1;
        // Ray direction
        double ray_angle = cub3d->player.angle + camera_x * (FOV / 2);
        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = -sin(ray_angle);

        // Cast the ray using DDA
        double wall_dist = cast_ray(cub3d, ray_angle);

        // Correct fisheye
        double corrected_dist = wall_dist * cos(ray_angle - cub3d->player.angle);

        // Wall height
        int line_height = (int)(SQUARE_SIZE *cub3d->mlx.size_y / corrected_dist);

        int draw_start = -line_height / 2 + cub3d->mlx.size_y / 2;
        int draw_end   = line_height / 2 + cub3d->mlx.size_y / 2;
        if (draw_start < 0) draw_start = 0;
        if (draw_end >= cub3d->mlx.size_y) draw_end = cub3d->mlx.size_y - 1;

        // DDA returns side and map positions
        int side = cast_ray_side(cub3d, ray_angle); // 0=vert,1=hor
        double ray_x = cub3d->player.position[0] / SQUARE_SIZE;
        double ray_y = cub3d->player.position[1] / SQUARE_SIZE;

        // Wall hit X position
        double wall_x;
        if (side == 0)
            wall_x = ray_y + corrected_dist * ray_dir_y;
        else
            wall_x = ray_x + corrected_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        // Texture X coordinate
        int tex_id;
        if (side == 0 && ray_dir_x > 0) { tex_id = 3; wall_x = 1 - wall_x; } // East
        else if (side == 0 && ray_dir_x < 0) tex_id = 2; // West
        else if (side == 1 && ray_dir_y > 0) tex_id = 1; // South
        else { tex_id = 0; wall_x = 1 - wall_x; } // North

        int tex_x = (int)(wall_x * cub3d->textures[tex_id].width);

        // Draw vertical strip
        for (int y = draw_start; y < draw_end; y++)
        {
            int d = (y - draw_start) ;
            int tex_y = ((d* cub3d->textures[tex_id].height) / line_height) ;

            int color = get_tex_pixel(&cub3d->textures[tex_id], tex_x, tex_y);
            img_pixel_put(&cub3d->img, x, y, color);
        }
    }

    // Push the image to window
    mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, cub3d->img.img, 0, 0);
}

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

    mlx_loop(cub3d->mlx.mlx);
    // ahasna(cub3d); // important for the freeing 
}