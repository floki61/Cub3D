/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:38:37 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/25 16:23:24 by oel-berh         ###   ########.fr       */
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

void	init_player(t_data	*img, int	y, int	x)
{
	img->py = (80 * y) + 35;
	img->px = (80 * x) + 35;
	img->ray.redline = 0;
	img->walkdirection = 0;
	img->turndirection = 0;
	img->drawmap	= 0;
	if(img->map[y][x] == 'N') // -PI/2
		img->rotationangle = -PI / 2;
	else if(img->map[y][x] == 'W')
		img->rotationangle = PI;
	else if(img->map[y][x] == 'S')
		img->rotationangle = PI / 2;
	else if(img->map[y][x] == 'E')
		img->rotationangle = 0;
	img->map[y][x] = '0';
	printf("angle: %f\n", img->rotationangle);
	img->rotationspeed = 2 * (PI / 180);
	img->movespeed = 10;
}

int	middle(char **map, t_data *img)
{
	int nop;
	int	i;
	int	n;

	i = 0;
	nop = 0;
	while (map[++i])
	{
		n = skip_spaces(map[i]);
		while (map[i][n])
		{
			if (map[i][n] == 'N' || map[i][n] == 'W' || map[i][n] == 'S' || map[i][n] == 'E')
			{	
				nop++;
				init_player(img, i, n);
			}
			else if(map[i][n] == '0')
			{
				if(map[i - 1][n] == ' ' || map[i + 1][n] == ' ' || map[i][n + 1] == ' ' || map[i][n - 1] == ' ')
				{
					printf("Y: %d, X: %d\n",i, n);
					return (-1);
				}
				else if(map[i - 1][n] == '\0' || map[i + 1][n] == '\0' || map[i][n + 1] == '\0' || map[i][n - 1] == '\0')
				{
					printf("Y: %d, X: %d\n",i, n);
					return (-1);
				}
				else if(map[i - 1][n] == '\t' || map[i + 1][n] == '\t' || map[i][n + 1] == '\t' || map[i][n - 1] == '\t')
					return(-1);
			}
			else if (map [i][n] != '1' && map[i][n] != ' ' && map[i][n] != '\t')
			{
				printf("Y: %d, X: %d\n",i, n);
				return (-1);
			}
			if(nop > 1)
				return (-1);
			n++;
		}
	}
	if(nop != 1)
		return (-1);
	return (0);
}

int	get_w(char	**map)
{
	int		i;
	int		x;
	int		g_w;

	i = 0;
	g_w = 0;
	while(map[i])
	{
		x =  ft_strlen(map[i]);
		if(g_w < x)
			g_w = x;
		i++;
	}
	return (g_w);
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
	img->g_w = get_w(img->map);
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
