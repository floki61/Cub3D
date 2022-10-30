/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 07:40:20 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/23 20:40:03 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dt;

	if (x < img->img_w && img->img_h > y)
	{
		dt = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dt = color;
	}
}

void	put_wall(t_data	*img)
{
	int	i;
	int	h;
	int	w;
	int	x;
	int	y;

	h = 0;
	i = W_WITHE / 100;
	x = (img->var.x * i) + 5;
	y = (img->var.y * i) + 5;
	while (h < i)
	{
		w = 0;
		while (w < i)
		{
			my_mlx_pixel_put(img, x + w, y + h, trgb(50, 60, 60, 60));
			w++;
		}
		h++;
	}
}

void	put_ground(t_data	*img)
{
	int	i;
	int	h;
	int	w;
	int	x;
	int	y;

	h = 0;
	i = W_WITHE / 100;
	x = (img->var.x * i) + 5;
	y = (img->var.y * i) + 5;
	while (h < i)
	{
		w = 0;
		while (w < i)
		{
			if (h == (i - 1) || w == (i - 1))
				my_mlx_pixel_put(img, x + w, y + h, trgb(50, 60, 60, 60));
			else
				my_mlx_pixel_put(img, x + w, y + h, trgb(50, 120, 120, 120));
			w++;
		}
		h++;
	}
}

void	put_myplayer(t_data *img)
{
	float	i;
	int		h;
	int		w;
	int		px;
	int		py;

	i = W_WITHE / 100;
	h = 0;
	px = (img->px / (TILE_SIZE / i)) + 5;
	py = (img->py / (TILE_SIZE / i)) + 5;
	i = W_WITHE / 500;
	while (h < i)
	{
		w = 0;
		while (w < i)
		{
			my_mlx_pixel_put(img, (px + w), (py + h), 0xffffff);
			w++;
		}
		h++;
	}
}

void	draw_map(t_data *img)
{
	img->var.y = -1;
	if ((img->g_w * W_WITHE) / 100 > W_WITHE
		|| (img->mapy * W_WITHE) / 100 > W_HIGHTE)
		return ;
	while (img->map[++img->var.y])
	{
		img->var.x = 0;
		while (img->map[img->var.y][img->var.x])
		{
			if (img->map[img->var.y][img->var.x] == '1')
				put_wall(img);
			else if (img->map[img->var.y][img->var.x] == ' '
				|| img->map[img->var.y][img->var.x] == '\t')
				put_wall(img);
			else if (img->map[img->var.y][img->var.x] == '0')
				put_ground(img);
			img->var.x++;
		}
		while (img->var.x < img->g_w)
		{
			put_wall(img);
			img->var.x++;
		}
	}
	put_myplayer(img);
}
