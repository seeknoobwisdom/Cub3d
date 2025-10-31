#include "../include/cub3d.h"


void open_xpm(t_cub3d *cub3d)
{
    if (!cub3d->no || (cub3d->fd_no = open(cub3d->no, O_RDONLY)) < 0)
	{
		close(cub3d->fd_no);
        error("Failed to open NO texture", 66, cub3d);
	}
	else
		close(cub3d->fd_no);
    if (!cub3d->so || (cub3d->fd_so = open(cub3d->so, O_RDONLY)) < 0)
	{
		close(cub3d->fd_so);
        error("Failed to open SO texture", 66, cub3d);
	}
	else
		close(cub3d->fd_so);
    if (!cub3d->we || (cub3d->fd_we = open(cub3d->we, O_RDONLY)) < 0)
	{
		close(cub3d->fd_we);
        error("Failed to open WE texture", 66, cub3d);
	}
	else
		close(cub3d->fd_we);
    if (!cub3d->ea || (cub3d->fd_ea = open(cub3d->ea, O_RDONLY)) < 0)
	{
		close(cub3d->fd_ea);
        error("Failed to open EA texture", 66, cub3d);
	}
	else
		close(cub3d->fd_ea);
}


void    check_name(t_cub3d  *cub3d)
{
    int len;
    char *filename = cub3d->filename;

    if (!filename)
        error("No filename provided", 65, cub3d);
    len = ft_strlen(filename);
    if (len < 5 || filename[len - 4] != '.' 
        || filename[len - 3] != 'c'
        || filename[len - 2] != 'u'
        || filename[len - 1] != 'b')
        error("Invalid file name. Must end with .cub", 65, cub3d);
}


int ends_with_xpm(const char *str)
{
    int len;

    if (!str)
        return (0);
    len = ft_strlen(str);
    if (len < 4)
        return (0);
    return (ft_strcmp(str + len - 4, ".xpm") == 0);
}


void check_names(t_cub3d *cub3d)
{
    if (!ends_with_xpm(cub3d->no) ||
        !ends_with_xpm(cub3d->so) ||
        !ends_with_xpm(cub3d->we) ||
        !ends_with_xpm(cub3d->ea))
    {
        error("Texture path must end with .xpm", 65, cub3d);
    }
}
