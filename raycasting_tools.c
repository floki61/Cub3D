/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:09:51 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 16:05:30 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	haswallat(t_data	*img, int x, int y)
{	
	if (y / TILE_SIZE > img->mapy)
		return (1);
	else if (x / TILE_SIZE > ft_strlen(img->map[y / TILE_SIZE]))
		return (1);
	if (img->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

void	raysfacing(t_data	*img, int i)
{
	if (img->rayangle > 0 && img->rayangle < PI)
		img->rays[i].rayfacing.down = 1;
	else
		img->rays[i].rayfacing.down = 0;
	if (img->rayangle < (0.5 * PI) || (img->rayangle > (1.5 * PI)))
		img->rays[i].rayfacing.right = 1;
	else
		img->rays[i].rayfacing.right = 0;
	img->rays[i].rayfacing.up = !img->rays[i].rayfacing.down;
	img->rays[i].rayfacing.left = !img->rays[i].rayfacing.right;
}

void	normalizeangle(t_data	*img)
{
	img->rayangle = remainder(img->rayangle, (2 * PI));
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

void	comp_raygrid(t_data	*img, int i)
{
	if (!img->rays[i].verthitdistance || (img->rays[i].verthitdistance
			> img->rays[i].horzhitdistance && img->rays[i].horzhitdistance))
	{
		img->rays[i].is_hor = 0;
		img->rays[i].wallhitx = img->rays[i].h_wallhitx;
		img->rays[i].wallhity = img->rays[i].h_wallhitx;
		img->rays[i].distance = img->rays[i].horzhitdistance;
	}
	else if (!img->rays[i].horzhitdistance || img->rays[i].verthitdistance
		< img->rays[i].horzhitdistance)
	{
		img->rays[i].is_hor = 1;
		img->rays[i].wallhitx = img->rays[i].v_wallhity;
		img->rays[i].wallhity = img->rays[i].v_wallhity;
		img->rays[i].distance = img->rays[i].verthitdistance;
	}
}
