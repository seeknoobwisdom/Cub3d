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


/* ---------clean exit------------- */
void    error(char  *error,int  exitcode, t_cub3d   *cub3d);
void    ahasna(t_cub3d   *cub3d);
void    free_array(char **array);


/* ---------test------------- */
void    print_map(t_cub3d *cub3d);
void    print_information(t_cub3d *cub3d);

/* ---------parce------------- */
void    main_parce(t_cub3d  *cub3d);
void 	check_undfind_simple(char	**map, t_cub3d	*cub3d);
 void	fill_map(t_cub3d *cub3d, char *line);
 void	fill_information(t_cub3d *cub3d);
 void    check_name(t_cub3d  *cub3d);
 void flood_fill(char **map, int x, int y, int *valid);
 void check_closed_map(char **map, int player_x, int player_y, t_cub3d *cub3d);
void find_player(char **map, int *px, int *py, t_cub3d *cub3d);
char *trim_after_key(const char *line);
char *trim_until_digit(const char *line);
void fix_end(t_cub3d *cub3d);
void remove_spaces(t_cub3d *cub3d);
void parse_color_str(const char *str, int type, t_cub3d *cub3d);
void parce_colors(t_cub3d *cub3d);
int ends_with_xpm(const char *str);
void check_names(t_cub3d *cub3d);
void normalize_map(t_cub3d *cub);
void check_map(t_cub3d *cub3d);
void open_xpm(t_cub3d *cub3d);

/* ---------utils------------- */
int abs(int i);
int squr(int num);
int	ft_atoi_custom(const char *str);
int	ft_isspace(unsigned char c);
int	ft_strcmp(const char *s1, const char *s2);
void	remove_newline(char **cub3d);
char	*ft_strcpy(char *dst, const char *src);
void normalize_map(t_cub3d *cub);


/* ---------execution------------- */
//mlx config
void    config_mlx(t_cub3d   *cub3d);
void img_pixel_put(t_img *img, int x, int y, int color);
void    load_texture(t_cub3d *cub3d, int id, char *path);
int get_tex_pixel(t_texture *tex, int x, int y);
// scene
void     main_execution(t_cub3d   *cub3d);
void config_player(t_cub3d   *cub3d, t_player *player);
double  cast_ray(t_cub3d    *cub3d, double  ray_angle);
double  cast_ray_side(t_cub3d    *cub3d, double  ray_angle);
 // main reneder function
void render_scene(t_cub3d *cub3d);
int game_loop(void *param);
int    check_area(int   test_x,int  test_y,t_cub3d * cub3d);
int keys_pressed(int keycode, void *param);


int rbga_color(int r, int b, int g, int a);// function take rbga valur return one number for the color

#endif