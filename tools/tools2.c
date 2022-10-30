/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 04:00:07 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/23 18:48:04 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	skip_lastspaces(char	*line)
{
	int	n;

	n = ft_strlen(line) - 1;
	while (line[n] == ' ' || line[n] == '\t')
		n--;
	return (n);
}

int	skip_spaces(char	*line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	init_player(t_data	*img, int y, int x)
{
	img->py = (TILE_SIZE * y) + (TILE_SIZE / 2) - 5;
	img->px = (TILE_SIZE * x) + (TILE_SIZE / 2) - 5;
	img->walkdirection = 0;
	img->turndirection = 0;
	if (img->map[y][x] == 'N')
		img->rotationangle = -PI / 2;
	else if (img->map[y][x] == 'W')
		img->rotationangle = PI;
	else if (img->map[y][x] == 'S')
		img->rotationangle = PI / 2;
	else if (img->map[y][x] == 'E')
		img->rotationangle = 0;
	img->map[y][x] = '0';
	img->rotationspeed = 2 * (PI / 180);
	img->movespeed = 10;
	img->pr += 1;
}

int	safe(char	**map, int i, int n)
{
	if ((map[i - 1][n] == ' ' || map[i + 1][n] == ' '
		|| map[i][n + 1] == ' ' || map[i][n - 1] == ' ')
		|| (map[i - 1][n] == '\0' || map[i + 1][n] == '\0'
		|| map[i][n + 1] == '\0' || map[i][n - 1] == '\0')
		|| (map[i - 1][n] == '\t' || map[i + 1][n] == '\t'
		|| map[i][n + 1] == '\t' || map[i][n - 1] == '\t'))
		return (0);
	return (1);
}

int	get_w(char	**map)
{
	int		i;
	int		x;
	int		g_w;

	i = 0;
	g_w = 0;
	while (map[i])
	{
		x = ft_strlen(map[i]);
		if (g_w < x)
			g_w = x;
		i++;
	}
	return (g_w);
}
