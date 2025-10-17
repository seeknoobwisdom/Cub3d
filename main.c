#include "include/cub3d.h"

void    init_ver(t_cub3d *cub3d)
{
    (void)cub3d;
    cub3d->fd_cub = -1;
    cub3d->fd_no = -1;
    cub3d->fd_so = -1;
    cub3d->fd_we = -1;
    cub3d->fd_ea = -1;
    cub3d->c = NULL;
    cub3d->f =NULL;
    cub3d->no = NULL;
    cub3d->so = NULL;
    cub3d->we = NULL;
    cub3d->ea = NULL;
    cub3d->map = NULL;
}

int main(int    arg, char   **argv)
{
    t_cub3d cub3d;
    init_ver(&cub3d);

    if(arg == 2)
    {
        cub3d.filename = argv[1];
        main_parce(&cub3d);
        main_execution(&cub3d);
    }
    else
        error("Usage error", 64, &cub3d);
    return(0);
}