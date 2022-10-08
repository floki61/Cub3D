/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:09:51 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/07 16:43:39 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   distancebetweenpoints(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int		haswallat(t_data	*img,int	x, int y)
{	
	if (y / TILE_SIZE > img->mapy)
		return (1);
	else if ( x / TILE_SIZE > ft_strlen(img->map[y / TILE_SIZE]))
		return (1);
	if(img->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return(1);
	return (0);
}

void	raysfacing(t_data	*img, int i)
{
	img->rays[i].rayfacing.down = img->rayangle > 0 && img->rayangle < PI;
	img->rays[i].rayfacing.up = !img->rays[i].rayfacing.down;
	img->rays[i].rayfacing.right = img->rayangle < (0.5 * PI) || img->rayangle > (1.5 * PI);
	img->rays[i].rayfacing.left = !img->rays[i].rayfacing.right;
}

void	normalizeangle(t_data	*img)
{
	img->rayangle =	remainder(img->rayangle, (2 * PI));
	if (img->rayangle < 0)
		img->rayangle = (2 * PI) + img->rayangle;
}


void	init_rays(t_data	*img)
{
	img->num_rays = (W_WITHE / WALL_STRIP_WIDTH);
	img->rayangle = img->rotationangle - (img->fov_angle / 2);
	if (!img->rays)
		img->rays = malloc(sizeof(t_cast) * img->num_rays);
}