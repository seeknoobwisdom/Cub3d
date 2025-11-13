#include "../include/cub3d.h"

void flood_fill(char **map, int x, int y, int *valid)
{
    if (y < 0 || x < 0|| !map[y] || !map[y][x] || map[y][x] == ' ')
    {
        *valid = 0;
        return;
    }
    if (map[y][x] == '1' || map[y][x] == 'F')
        return;
    map[y][x] = 'F';
    flood_fill(map, x + 1, y, valid);
    flood_fill(map, x - 1, y, valid);

    flood_fill(map, x, y + 1, valid);
    flood_fill(map, x, y - 1, valid);
}




void check_closed_map(char **map, int player_x, int player_y, t_cub3d *cub3d)
{
	char **copy;
    int valid = 1;
	int j;
	int i;

	i = 0;
	j = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		error("System error (e.g., malloc failed, resource unavailable)", 71, cub3d);
    while (j < i)
	{
        copy[j] = ft_strdup(map[j]);
		j++;
	}
    copy[i] = NULL;
    flood_fill(copy, player_x, player_y, &valid);
	free_array(copy);
    if (!valid)
        error("Map is not closed", 65, cub3d);
}


void find_player(char **map, int *px, int *py, t_cub3d *cub3d)
{
    int y = 0;
    int found = 0;
    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' ||
                map[y][x] == 'E' || map[y][x] == 'W')
            {
                if (found)
                    error("Multiple player positions", 65, cub3d);
                *px = x;
                *py = y;
                found = 1;
            }
            x++;
        }
        y++;
    }
    if (!found)
        error("No player found in map", 65, cub3d);
}

void 	check_undfind_simple(char	**map, t_cub3d	*cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(map[i])
	{
		while(map[i][j] != '\0')
		{
			if (map[i][j] != 'N'&& map[i][j] !='E'&& map[i][j] !='W'&& map[i][j] !='S'&& map[i][j] !=' '&& map[i][j] !='1'&& map[i][j] !='0' && map[i][j] !='\n')
			{
				error("Data format error (bad input file, corrupted data)", 65, cub3d);
			}
			j++;
		}
		j = 0;
		i++;
	}
}


void check_map(t_cub3d *cub3d)
{
    int player_x, player_y;

    if (!cub3d->map)
	{
        error("No map found", 65, cub3d);
	}
	normalize_map(cub3d);
    find_player(cub3d->map, &player_x, &player_y, cub3d);
    check_closed_map(cub3d->map, player_x, player_y, cub3d);

}