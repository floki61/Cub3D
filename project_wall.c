/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:56:33 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/23 20:42:01 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_react(t_data *data, int x, int hight)
{
	int	j;
	int	top_pixl;
	int	bottem_pixl;
	int	distancefromtop;

	top_pixl = get_top(hight);
	bottem_pixl = get_bottem(hight);
	pint_sc_gr(data, top_pixl, bottem_pixl, x);
	data->textureoffsetx = x_ofset(data, x);
	j = top_pixl;
	while (j < bottem_pixl)
	{
		distancefromtop = j + (hight / 2) - (W_HIGHTE / 2);
		data->textureoffsety = distancefromtop * TEXTUR_HIGHT / hight;
		draw_the_3d(data, (j * data->line_length + x
				*(data->bits_per_pixel / 8)),
			(data->textureoffsety * TILE_SIZE) + data->textureoffsetx, x);
		j++;
	}
}

void	ray_diriction(t_data	*data, int i)
{
	if (data->rays[i].is_hor)
	{
		if (data->rays[i].rayfacing.right)
			data->rays[i].dir = 'E';
		else if (data->rays[i].rayfacing.left)
			data->rays[i].dir = 'W';
	}
	else
	{
		if (data->rays[i].rayfacing.down)
			data->rays[i].dir = 'S';
		else if (data->rays[i].rayfacing.up)
			data->rays[i].dir = 'N';
	}
}

void	rander_3dprojectedwall(t_data *data)
{
	int	i;
	int	distance_projection_plan;
	int	wall_hight;
	int	correct_dest;

	distance_projection_plan = (W_WITHE / 2) / tan(data->fov_angle / 2);
	i = 0;
	while (i < data->num_rays)
	{
		ray_diriction(data, i);
		correct_dest = (int)data->rays[i].distance
			* cos(data->rays[i].rayangle_pro - data->rotationangle);
		wall_hight = (int)((TILE_SIZE / ((double)correct_dest))
				* ((double)distance_projection_plan));
		if (correct_dest == 0)
			wall_hight = W_HIGHTE;
		ft_react(data, i, wall_hight);
		i++;
	}
}
