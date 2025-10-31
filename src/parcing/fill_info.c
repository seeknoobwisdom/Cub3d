#include "../include/cub3d.h"


static int	is_identifier(char *line, char *id)
{
	int i;

	i = 0;
	while (id[i] && line[i] == id[i])
		i++;
	if (id[i] == '\0' && (line[i] == ' ' || line[i] == '\t'))
		return (1);
	return (0);
}

static void	save_identifier(t_cub3d *cub3d, char *line)
{
	if (is_identifier(line, "NO") && !cub3d->no)
		cub3d->no = ft_strdup(line + 2);
	else if (is_identifier(line, "SO") && !cub3d->so)
		cub3d->so = ft_strdup(line + 2);
	else if (is_identifier(line, "WE") && !cub3d->we)
		cub3d->we = ft_strdup(line + 2);
	else if (is_identifier(line, "EA") && !cub3d->ea)
		cub3d->ea = ft_strdup(line + 2);
	else if (is_identifier(line, "F") && !cub3d->f)
		cub3d->f = ft_strdup(line + 1);
	else if (is_identifier(line, "C") && !cub3d->c)
		cub3d->c = ft_strdup(line + 1);
	else
	{
		free(line);
		error("Duplicate or invalid identifier in .cub file", 67, cub3d);
	}
}

void	fill_map(t_cub3d *cub3d, char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	cub3d->map = malloc(sizeof(char *) * 2);
	char	**new;
	new = NULL;
	while (line)
	{
		if (*line == '\n') // empty line inside map = invalid
		{
			free(line);
			error("Invalid empty line inside map", 68, cub3d);
		}
		cub3d->map[i] = ft_strdup(line); // duplicate before freeing
		cub3d->map[i + 1] = NULL;
		free(line);
		i++;
		line = get_next_line(cub3d->fd_cub);
		if (line)
		{
			j = 0;
			while (cub3d->map[j])
				j++;
			new = malloc(sizeof(char *) * (j + 2));
			j = 0;
			while (cub3d->map[j])
			{
				new[j] = ft_strdup(cub3d->map[j]);
				j++;
			}
			new[j] = NULL;
			free_array(cub3d->map);
			cub3d->map = new;
		}
		else
		{
			cub3d->map[i] = NULL;
			break;
		}
	}
}


void	fill_information(t_cub3d *cub3d)
{
	char	*line;
	int		found;

	found = 0;
    line = get_next_line(cub3d->fd_cub);
	while (line)
	{
		if (*line == '\n') // skip empty lines
		{
			free(line);
			line = get_next_line(cub3d->fd_cub);
			continue;
		}
		save_identifier(cub3d, line);
		free(line);
		found++;
        line = get_next_line(cub3d->fd_cub);
		if (found == 6 || !line || *line == '1' || *line == '0' || *line == ' ')
			break ;
	}
	if (found < 6)
	{
		free(line);
		error("Missing one or more identifiers (NO, SO, WE, EA, F, C)", 68, cub3d);
	}
	while(*line == '\n')
	{
		free(line);
		line = get_next_line(cub3d->fd_cub);
	}
	if (!line || (*line != '1' && *line != '0' && *line != ' '))
	{
		free(line);
		error("Missing the map or invalid map", 68, cub3d);
	}
	fill_map(cub3d, line);
}