/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 07:40:20 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 08:48:38 by oel-berh         ###   ########.fr       */
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

	i = 0;
	h = 0;
	x = W_WITHE - (img->g_w * 20) - 10;
	y = W_HIGHTE - (img->mapy * 20) - 10;
	x += (img->var.x * 20);
	y += (img->var.y * 20);
	while (h < 20)
	{
		w = 0;
		while (w < 20)
		{
			my_mlx_pixel_put(img, x + w, y + h, trgb(50, 60, 60, 60));
			i++;
			w++;
		}
		h++;
	}
}

void	put_ground(t_data	*img)
{
	int	h;
	int	w;
	int	x;
	int	y;

	h = 0;
	x = W_WITHE - (img->g_w * 20) - 10;
	y = W_HIGHTE - (img->mapy * 20) - 10;
	x += (img->var.x * 20);
	y += (img->var.y * 20);
	while (h < 20)
	{
		w = 0;
		while (w < 20)
		{
			if (h == 19 || w == 19)
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
	int		h;
	int		w;
	int		px;
	int		py;
	float	x;

	h = 0;
	px = W_WITHE - (img->g_w * 20) - 10;
	py = W_HIGHTE - (img->mapy * 20) - 10;
	x = (TILE_SIZE / 20.f);
	px += (img->px / x);
	py += (img->py / x);
	while (h < 4)
	{
		w = 0;
		while (w < 4)
		{
			my_mlx_pixel_put(img, (px + w), (py + h), 0xffffff);
			w++;
		}
		h++;
	}
}

void	draw_map(t_data *img)
{
	img->var.y = 0;
	while (img->map[img->var.y])
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
		img->var.y++;
	}
	put_myplayer(img);
}
