/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/23 20:40:12 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw(t_data *img)
{
	castallrays(img);
	rander_3dprojectedwall(img);
	if (img->minimap)
		draw_map(img);
}

int	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit (0);
	return (0);
}

int	loop_game(t_data	*img)
{
	update(img);
	if (!img->img)
	{
		img->img = mlx_new_image(img->mlx, W_WITHE, W_HIGHTE);
			img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
		make_b_image (img);
	}
	draw(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
	mlx_hook(img->mlx_win, 3, 2L, key_hook2, img);
	return (0);
}

int	open_window(t_data *img)
{
	img->mapx = ft_strlen(img->map[0]);
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, W_WITHE, W_HIGHTE, "game");
	img->img_w = img->mapx * TILE_SIZE;
	img->img_h = img->mapy * TILE_SIZE;
	read_images(img);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}
