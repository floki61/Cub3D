/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:28:19 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 15:58:47 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_direction1(t_data	*img)
{
	int		px;
	int		py;
	double	rotationangle;		

	rotationangle = img->rotationangle + (img->fov_angle * 1.5
			* img->walkdirection2);
	img->movestep = img->movespeed;
	while (img->movestep >= 0)
	{
		px = (img->px + cos(rotationangle) * img->movestep);
		py = (img->py + sin(rotationangle) * img->movestep);
		if (img->map[py / TILE_SIZE][px / TILE_SIZE] == '0'
			&& img->map[py / TILE_SIZE][(px + 10) / TILE_SIZE] == '0'
			&& img->map[(py + 10) / TILE_SIZE][px / TILE_SIZE] == '0'
			&& img->map[(py + 10) / TILE_SIZE][(px + 10) / TILE_SIZE] == '0')
		{
			img->px = px;
			img->py = py;
			return ;
		}
		img->movestep--;
	}
}

void	update_direction0(t_data	*img)
{
	int	px;
	int	py;

	while (img->movespeed >= 0)
	{
		img->movestep = img->walkdirection * img->movespeed;
		px = (img->px + cos(img->rotationangle) * img->movestep);
		py = (img->py + sin(img->rotationangle) * img->movestep);
		if (img->map[py / TILE_SIZE][px / TILE_SIZE] == '0'
			&& img->map[py / TILE_SIZE][(px + 10) / TILE_SIZE] == '0'
			&& img->map[(py + 10) / TILE_SIZE][px / TILE_SIZE] == '0'
			&& img->map[(py + 10) / TILE_SIZE][(px + 10) / TILE_SIZE] == '0')
		{
			img->px = px;
			img->py = py;
			img->movespeed = 10;
			return ;
		}
		img->movespeed--;
	}
	img->movespeed = 10;
}

void	update(t_data	*img)
{
	img->rotationangle += img->turndirection * img->rotationspeed;
	if (img->walkdirection)
		update_direction0(img);
	if (img->walkdirection2)
		update_direction1(img);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 53)
		exit (0);
	else if (keycode == 1)
		img->walkdirection = -1;
	else if (keycode == 13)
		img->walkdirection = 1;
	else if (keycode == 123)
		img->turndirection = -1;
	else if (keycode == 124)
		img->turndirection = 1;
	if (keycode == 2)
		img->walkdirection2 = 1;
	else if (keycode == 0)
		img->walkdirection2 = -1;
	else if (keycode == 48)
		img->minimap = 1;
	return (0);
}

int	key_hook2(int keycode, t_data *img)
{
	if (keycode == 1 || keycode == 13)
		img->walkdirection = 0;
	else if (keycode == 123 || keycode == 124)
		img->turndirection = 0;
	else if (keycode == 0 || keycode == 2)
		img->walkdirection2 = 0;
	else if (keycode == 48)
		img->minimap = 0;
	return (0);
}
