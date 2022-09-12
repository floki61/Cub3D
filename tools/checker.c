/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:38:37 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/12 15:26:51 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int skip_lastspaces(char    *line)
{
	int	n;

	n = ft_strlen(line) - 1;
	while (line[n] == ' ' || line[n] == '\t')
		n--;
	return (n);
}

int skip_spaces(char    *line)
{
	int i;

	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int	height(char **map, t_data *img)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][skip_spaces(map[i])] != '1' || map[i][skip_lastspaces(map[i])] != '1')
			return (-1);
		i++;
	}
	img->mapy = i;
	return (i);
}

int	width(char **map, int i) //-> firt line must be 11111111111111
{
	int	n;

	n = skip_spaces(map[i]);
	while (map[i][n])
	{	
		if (map[i][n] != '1' && map[i][n] != ' ' && map[i][n] != '\t')
			return (-1);
		n++;
	}
	return (n);
}

int	middle(char **map, t_data *img)
{
	int	i;
	int	n;

	i = 1;
	while (map[++i])
	{
		n = skip_spaces(map[i]);
		while (map[i][n])
		{
			if (map[i][n] == 'P')
			{
				map[i][n] = '0';
				img->px = (80 * n) + 35;
				img->py = (80 * i) + 35;
			}
			else if(map[i][n] == '0')
			{
				if(map[i - 1][n] == ' ' || map[i + 1][n] == ' ' || map[i][n + 1] == ' ' || map[i][n - 1] == ' ')
					return(-1);	
				else if(map[i - 1][n] == '\0' || map[i + 1][n] == '\0' || map[i][n + 1] == '\0' || map[i][n - 1] == '\0')
					return(-1);	
			}
			else if (map [i][n] != '1' && map[i][n] != ' ' && map[i][n] != '\t')
				return (-1);
			n++;
		}
	}
	return (0);
}

int	check_map(char	**map, t_data	*img)
{
	if ((height(map, img)) == -1)
	{
		printf("height error\n");
		return (0);
	}
	if ((width(map, 0)) == -1)
	{
		printf("width0 error\n");
		return (0);
	}
	if ((width(map, img->mapy - 1)) == -1)
	{
		printf("width1 error\n");
		return (0);
	}
	if ((middle(map, img)) == -1)
	{
		printf("middle error\n");
		return (0);
	}
	return (1);
}



int	check_name(int argc, char *str)
{
	int		i;
	int		j;
	char	*s;
	
	if(argc != 2)
		exit(0);
	i = ft_strlen(str) - 4;
	j = 0;
	s = ".cub";
	if (i < 0)
		return (1);
	while ((str[i] != '\0' || s[j] != '\0') && (str[j] == s[j]))
	{
		i++;
		j++;
	}
	if(str[i] - s[j] != 0)
	{
		ft_putstr("Error Invalid File");
		exit(0);
	}
	return (0);
}
