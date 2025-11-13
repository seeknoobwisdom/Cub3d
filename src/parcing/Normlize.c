#include "../include/cub3d.h"



char *trim_after_key(const char *line)
{
    int i = 0;
    while (line[i] && !ft_isspace(line[i]))
        i++;               // Skip key
    while (line[i] && ft_isspace(line[i]))
        i++;               // Skip spaces after key
    return ft_strdup(line + i);
}

// Trim until first digit (colors)
char *trim_until_digit(const char *line)
{
    int i = 0;
    while (line[i] && !ft_isdigit(line[i]))
        i++;               // Skip until first number
    return ft_strdup(line + i);
}

// Update struct member
void	remove_newline(char **cub3d)
{
	int	i;

	i =0;
	while(cub3d[0][i])
		i++;
	if (cub3d[0][i - 1] == '\n')
		cub3d[0][i - 1] = '\0';
}
void fix_end(t_cub3d *cub3d)
{
	int i;

	i = 0;
	if (cub3d->no)
        remove_newline(&cub3d->no);
    if (cub3d->so)
        remove_newline(&cub3d->so);
    if (cub3d->we)
        remove_newline(&cub3d->we);
    if (cub3d->ea)
        remove_newline(&cub3d->ea);
    if (cub3d->f)
        remove_newline(&cub3d->f);
    if (cub3d->c)
	{
        remove_newline(&cub3d->c);
	}
	while(cub3d-> map[i])
	{
		remove_newline(&cub3d->map[i]);
		i++;
	}
	check_undfind_simple(cub3d->map, cub3d);
}
void remove_spaces(t_cub3d *cub3d)
{
    char *tmp;


	tmp = NULL;
    if (cub3d->no)
    {
        tmp = trim_after_key(cub3d->no);
        free(cub3d->no);
        cub3d->no = tmp;
    }
    if (cub3d->so)
    {
        tmp = trim_after_key(cub3d->so);
        free(cub3d->so);
        cub3d->so = tmp;
    }
    if (cub3d->we)
    {
        tmp = trim_after_key(cub3d->we);
        free(cub3d->we);
        cub3d->we = tmp;
    }
    if (cub3d->ea)
    {
        tmp = trim_after_key(cub3d->ea);
        free(cub3d->ea);
        cub3d->ea = tmp;
    }

    if (cub3d->f)
    {
        tmp = trim_until_digit(cub3d->f);
        free(cub3d->f);
        cub3d->f = tmp;
    }
    if (cub3d->c)
    {
        tmp = trim_until_digit(cub3d->c);
        free(cub3d->c);
        cub3d->c = tmp;
    }
	fix_end(cub3d);
}

void parse_color_str(const char *str, int type, t_cub3d *cub3d)
{
    char **parts;
    int i;
	int	j;
	int	*dest;

	j = 0;
	if (type == 1)
		dest =cub3d->floor;
	else
		dest =cub3d->ceiling;
    parts = ft_split(str, ','); // you already have ft_split in libft
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_array(parts);
        error("Invalid color format (must be R,G,B)", 67, cub3d);
	}

    i = 0;
	while(parts[i])
	{

		while(parts[i][j])
		{
			if(!ft_isdigit(parts[i][j]))
			{

				free_array(parts);
				error("Color values must a digit!!!", 68, cub3d);
			}
			j++;
		}
		j=0;
		i++;
	}
	i = 0;
    while (i < 3)
    {
        dest[i] = ft_atoi_custom(parts[i]);
        if (dest[i] < 0 || dest[i] > 255)
		{
			free_array(parts);
            error("Color values must be between 0 and 255", 68, cub3d);
		}
        i++;
    }
	
    free_array(parts); // helper to free **parts
}

void parce_colors(t_cub3d *cub3d)
{
    if (cub3d->f)
        parse_color_str(cub3d->f, 1, cub3d);
    if (cub3d->c)
        parse_color_str(cub3d->c, 2, cub3d);
}
