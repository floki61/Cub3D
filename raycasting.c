/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:10:15 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 16:04:43 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	norm_hor_grid(t_data	*img, float xstep, float ystep, int i)
{
	while (img->h_xintercept >= 0
		&& img->h_xintercept <= TILE_SIZE * img->mapx
		&& img->h_yintercept >= 0
		&& img->h_yintercept <= TILE_SIZE * img->mapy)
	{
		if (img->rays[i].rayfacing.up)
			img->h_yintercept -= 1;
		if (haswallat(img, img->h_xintercept, img->h_yintercept))
		{
			if (img->rays[i].rayfacing.up)
				++img->h_yintercept;
			img->rays[i].h_wallhitx = img->h_xintercept;
			img->rays[i].h_wallhity = img->h_yintercept;
			img->rays[i].horzhitdistance = distancebetweenpoints(img->px + 5,
					img->py + 5, img->h_xintercept, img->h_yintercept);
			break ;
		}
		else
		{
			if (img->rays[i].rayfacing.up)
				img->h_yintercept += 1;
			img->h_xintercept += xstep;
			img->h_yintercept += ystep;
		}
	}
}

void	horizontal_raygrid(t_data	*img, int i)
{
	float	xstep;
	float	ystep;

	img->rays[i].horzhitdistance = 0;
	img->h_yintercept = floor((img->py + 5) / TILE_SIZE) * TILE_SIZE;
	if (img->rays[i].rayfacing.down)
		img->h_yintercept += TILE_SIZE;
	img->h_xintercept = img->px + 5 + (img->h_yintercept - img->py - 5)
		/ tan(img->rayangle);
	ystep = TILE_SIZE;
	if (img->rays[i].rayfacing.up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(img->rayangle);
	if (img->rays[i].rayfacing.left && xstep > 0)
		xstep *= -1;
	else if (img->rays[i].rayfacing.right && xstep < 0)
		xstep *= -1;
	norm_hor_grid(img, xstep, ystep, i);
}

void	norm_ver_g(t_data	*img, float xstep, float ystep, int i)
{
	while (img->v_xintercept >= 0
		&& img->v_xintercept <= TILE_SIZE * img->mapx
		&& img->v_yintercept >= 0
		&& img->v_yintercept <= TILE_SIZE * img->mapy)
	{
		if (img->rays[i].rayfacing.left)
			img->v_xintercept--;
		if (haswallat(img, img->v_xintercept, img->v_yintercept))
		{
			if (img->rays[i].rayfacing.left)
				++img->v_xintercept;
			img->rays[i].v_wallhitx = img->v_xintercept;
			img->rays[i].v_wallhity = img->v_yintercept;
			img->rays[i].verthitdistance = distancebetweenpoints(img->px + 5,
					img->py + 5, img->v_xintercept, img->v_yintercept);
			break ;
		}
		else
		{
			if (img->rays[i].rayfacing.left)
				++img->v_xintercept;
			img->v_xintercept += xstep;
			img->v_yintercept += ystep;
		}
	}
}

void	vertical_raygrid(t_data	*img, int i)
{
	float		xstep;
	float		ystep;

	img->rays[i].verthitdistance = 0;
	img->v_xintercept = floor((img->px + 5) / TILE_SIZE) * TILE_SIZE;
	if (img->rays[i].rayfacing.right)
		img->v_xintercept += TILE_SIZE;
	img->v_yintercept = img->py + 5 + (img->v_xintercept - img->px - 5)
		* tan(img->rayangle);
	xstep = TILE_SIZE;
	if (img->rays[i].rayfacing.left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(img->rayangle);
	if (img->rays[i].rayfacing.up && ystep > 0)
		ystep *= -1;
	else if (img->rays[i].rayfacing.down && ystep < 0)
		ystep *= -1;
	norm_ver_g(img, xstep, ystep, i);
}

void	castallrays(t_data	*img)
{
	int	i;

	i = 0;
	init_rays(img);
	while (i < img->num_rays)
	{
		normalizeangle(img);
		raysfacing(img, i);
		horizontal_raygrid(img, i);
		vertical_raygrid(img, i);
		comp_raygrid(img, i);
		img->rays[i].rayangle_pro = img->rayangle;
		img->rayangle += img->fov_angle / img->num_rays;
		i++;
	}
}
