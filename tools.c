/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:49:41 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 16:04:20 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char	**str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
}

float	distancebetweenpoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	is_num(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' && str[i] > '9')
			return (0);
	return (1);
}

void	init_color(t_data *img, char **color, int c)
{
	if (c == 'f')
	{
		img->color.redfloor = atoi(color[0]);
		img->color.greenfloor = atoi(color[1]);
		img->color.bluefloor = atoi(color[2]);
		img->color.findex = 1;
	}
	else if (c == 'c')
	{
		img->color.redceilling = atoi(color[0]);
		img->color.greenceilling = atoi(color[1]);
		img->color.blueceilling = atoi(color[2]);
		img->color.cindex = 1;
	}
}

int	check_color(char *color)
{
	int	ncolor;

	if (is_num(color))
	{
		ncolor = atoi(color);
		if (ncolor >= 0 && ncolor <= 255)
			return (ncolor);
	}
	printf("--------ERROR IN COLOR--------\n");
	exit (0);
}
