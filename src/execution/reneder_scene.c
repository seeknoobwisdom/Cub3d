#include "../include/cub3d.h"

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
    if (ray_dir_x < 0)// by this we caqn understand which side it will hit the4 left or rigt 
    {
    step_x = -1;
    side_dist_x = (ray_x - map_x) * delta_dist_x;
    }
    else
    {
    step_x = 1;
    side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x;// becouse map_x will always be smaller becouse it alwasys the int part and we need the float part to decided the length of the step
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

                            //those help u to find left or rigth up or down wall small corrction
                            //              here   
    if (side == 0)////////////////////////-------- from the ray equation ray_position = ray_origin + ray_direction * distance 
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

void render_scene(t_cub3d *cub3d)
{
    // Clear image (black)
    ft_memset(cub3d->img.addr, 0, cub3d->img.line_length * cub3d->img.height);

    for (int x = 0; x < cub3d->mlx.size_x; x++)
    {
        // Map x to camera space (-1 to 1)
        double camera_x = (2 * x / (double)cub3d->mlx.size_x) - 1;// CONVERT THE CAMERA COORDONATE TO 1 _> -1
        // Ray direction
        double ray_angle = cub3d->player.angle + (camera_x * (FOV / 2));// this is used for colum by column it move the vison slighthly everytime 
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
        int y = 0;
        while (y < draw_start)
        {
            int color = rbga_color(cub3d->ceiling[0],cub3d->ceiling[1], cub3d->ceiling[2], 0 );
            img_pixel_put(&cub3d->img, x, y, color);
            y++;
        }

        for (int y = draw_start; y < draw_end; y++)
        {
            int d = (y - draw_start) ;
            int tex_y = ((d* cub3d->textures[tex_id].height) / line_height) ;

            int color = get_tex_pixel(&cub3d->textures[tex_id], tex_x, tex_y);
            img_pixel_put(&cub3d->img, x, y, color);
        }
        y = draw_end;
        while (y < cub3d->mlx.size_y -1)
        {
         int color = rbga_color(cub3d->floor[0],cub3d->floor[1], cub3d->floor[2], 0 );
            img_pixel_put(&cub3d->img, x, y, color);
            y++;
        }        
    }

    // Push the image to window
    mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, cub3d->img.img, 0, 0);
}