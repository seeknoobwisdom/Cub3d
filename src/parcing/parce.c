#include "../include/cub3d.h"






void normalize_map(t_cub3d *cub)
{
    int i, j;
    int max_len = 0;

    // Find the maximum row length
    for (i = 0; cub->map[i]; i++)
    {
        int len = ft_strlen(cub->map[i]);
        if (len > max_len)
            max_len = len;
    }

    // Pad all rows to max_len
    for (i = 0; cub->map[i]; i++)
    {
        int len = ft_strlen(cub->map[i]);
        if (len < max_len)
        {
            char *new_row = malloc(max_len + 1);
            ft_strcpy(new_row, cub->map[i]);
            for (j = len; j < max_len; j++)
                new_row[j] = ' ';  // empty space = wall gap
            new_row[max_len] = '\0';
            free(cub->map[i]);
            cub->map[i] = new_row;
        }
    }
}




void    main_parce(t_cub3d  *cub3d)
{
    check_name(cub3d);
    cub3d->fd_cub = open(cub3d->filename, O_RDONLY);
    if (0 > cub3d->fd_cub)
        error("Cannot open input (file not found / permission denied)", 66, cub3d);
    fill_information(cub3d);
	remove_spaces(cub3d);
	check_map(cub3d);
	open_xpm(cub3d);
	/*
	typedef struct s_cub3d
{
    t_mlx  mlx;
    char    *filename;
    int     fd_cub;
    char    **map;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *c;
    char    *f;

    int floor[3];
    int  ceiling[3];
}t_cub3d;
	*/
	check_names(cub3d); //should all end wilth .xpm  for inital data for the no so we ea
	parce_colors(cub3d);//split it by , atoi it check if it execeded 255 should be unvaild or below the 0  will be saved on floor and on ceiling 
	// function of error   for example error("Cannot open input (file not found / permission denied)", 66, cub3d);
	print_information(cub3d);
    // check_texture();
    // check_map();
}