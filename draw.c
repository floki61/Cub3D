/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/07 16:40:19 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < img->img_w && img->img_h > y)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void	put_wall(t_data	*img)
{
	int i;
	int	h;
	int w;
	
	i = 0;
	h = 0;
	int	x = W_WITHE - (img->g_w * 20) - 10;
	int	y = W_HIGHTE - (img->mapy * 20) - 10;
	x += (img->var.x * 20);
	y += (img->var.y * 20);
	while(h < 20)
	{
		w = 0;
		while (w < 20)
		{
			my_mlx_pixel_put(img, x + w, y + h, create_trgb(50, 60,60,60));
			i++;
			w++;
		}
		h++;
	}
}


void	put_ground(t_data	*img)
{
	int	h;
	int w;
	
	h = 0;
	int	x = W_WITHE - (img->g_w * 20) - 10;
	int	y = W_HIGHTE - (img->mapy * 20) - 10;
	x += (img->var.x * 20);
	y += (img->var.y * 20);
	while(h < 20)
	{
		w = 0;
		while (w < 20)
		{
			if(h == 19 || w == 19 )
				my_mlx_pixel_put(img, x + w, y + h , create_trgb(50, 60,60,60));
			else
				my_mlx_pixel_put(img, x + w, y + h, create_trgb(50, 120,120,120));
			w++;
		}
		h++;
	}
}

void	put_myplayer(t_data *img)
{
	int	h;
	int w;

	h = 0;
	int px = W_WITHE - (img->g_w * 20) - 10;
	int py = W_HIGHTE - (img->mapy * 20) - 10;
	float x = (TILE_SIZE / 20.f);
	px += (img->px / x);
	py += (img->py / x);
	while(h < 4)
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

void ft_react(t_data *data, int x, int hight)
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

void rander_3dprojectedwall(t_data *data)
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
		correct_dest = data->rays[i].distance
			* cos(data->rays[i].rayangle_pro - data->rotationangle);
		wall_hight = (int)((TILE_SIZE / ((double)correct_dest))
				* ((double)distance_projection_plan));
		// if (correct_dest == 0)
		// 	wall_hight = 0;
		// printf("indx [%d]num [%d] corr >> %d\n",i , data->num_rays, wall_hight);
		ft_react(data, i, wall_hight);
		i++;
	}
}

void	drawrays(t_data	*img)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < img->num_rays)
	{
		j = 1;
		while (img->rays[i].distance > j)
		{
			exit(0);
			x = img->px + 5 + cos(img->rays[i].rayangle_pro) * j;
			y = img->py + 5 + sin(img->rays[i].rayangle_pro) * j;
			my_mlx_pixel_put(img, x * 0.2, y * 0.2, 0x800080);
			j++;
		}
		i++;
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
	exit(0);
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