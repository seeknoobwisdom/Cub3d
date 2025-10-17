#include "../include/cub3d.h"

#include "cub3d.h"
#include <stdio.h>

static unsigned int	ret_check_custom(unsigned int i, int sign)
{
	if (i > 2147483647 && sign == 1)
		return (-2000);
	if (i > 2147483648 && sign == -1)
		return (2000);
	else
		return (i * sign);
}

int	ft_atoi_custom(const char *str)
{
	unsigned int	num;
	int				found;
	int				sign;

	num = 0;
	found = 0;
	sign = 1;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			found = 1;
			num = (num * 10) + (*str - '0');
		}
		else if ((*str == '+' || *str == '-') && found == 0)
		{
			found = 1;
			sign = 44 - *str;
		}
		else if ((*str != ' ' && !(*str >= '\t' && *str <= '\r')
				&& found == 0) || found == 1)
			break ;
		str++;
	}
	return ((int) ret_check_custom(num, sign));
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

int	ft_isspace(unsigned char c)
{
	if (c && c == ' ')
		return (c);
	return(0);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


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