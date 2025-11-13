#include "../include/cub3d.h"


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

int rbga_color(int r, int g, int b, int a)// function take rbga valur return one number for the color
{
	return (a << 24 | r << 16 | g << 8 | b );
}
