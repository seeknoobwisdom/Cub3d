#include "../include/cub3d.h"

void    print_map(t_cub3d *cub3d)
{
    int i = 0;

    printf("=== Map ===\n");
    if (!cub3d->map)
    {
        printf("(no map loaded)\n");
        return;
    }
    while (cub3d->map[i])
    {
        printf("%s\n", cub3d->map[i]); 
        i++;
    }


    printf("\n==========================\n");
}

void    print_information(t_cub3d *cub3d)
{
    printf("=== Parsed Information ===\n");
    printf("NO: %s\n", cub3d->no ? cub3d->no : "(missing)");
    printf("SO: %s\n", cub3d->so ? cub3d->so : "(missing)");
    printf("WE: %s\n", cub3d->we ? cub3d->we : "(missing)");
    printf("EA: %s\n", cub3d->ea ? cub3d->ea : "(missing)");
	printf("Floor   -> R:%d G:%d B:%d\n",
       cub3d->floor[0], cub3d->floor[1], cub3d->floor[2]);

printf("Ceiling -> R:%d G:%d B:%d\n",
       cub3d->ceiling[0], cub3d->ceiling[1], cub3d->ceiling[2]);

    printf("==========================\n");
	print_map(cub3d);
}
