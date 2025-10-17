#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"


typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
}   t_texture;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    int size_x;
    int size_y;
}t_mlx;

typedef struct s_player
{
    double position[2]; // (x, y)
    double  dir[2];// up, down, left, rigth
    double  fov[2]; //  +0.66 and -0.66 to the diraction
    int  cameraX[2];// ((x * 2) / WEDTH) - 1
    int  n_rays;
    double angle;
    int movespeed;
    float   rotation_speed;
    float   fov_angle;
    char c;
}t_player;

typedef struct s_cub3d
{
    t_player    player;
    t_mlx  mlx;
    t_img   img;
    t_texture   textures[4]; // 0=N, 1=S, 2=E, 3=W
    char    *filename;
    int     fd_cub;
    char    **map;
    char    *no;
    int     fd_no;
    char    *so;
    int     fd_so;
    char    *we;
    int     fd_we;
    char    *ea;
    int     fd_ea;
    char    *c;
    char    *f;

    int floor[3];
    int  ceiling[3];
}t_cub3d;

#define SQUARE_SIZE 32
#define FOV (60*M_PI/180) // radian to get accepted by math library 
#define RES 2
#define RADIUS  5
#define ARROW_LEN 32 * 10

void    error(char  *error,int  exitcode, t_cub3d   *cub3d);
void    main_parce(t_cub3d  *cub3d);
void     main_execution(t_cub3d   *cub3d);
void    ahasna(t_cub3d   *cub3d);
void    free_array(char **array);
void    print_map(t_cub3d *cub3d);

#endif