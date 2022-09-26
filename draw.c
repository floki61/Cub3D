/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/26 15:42:24 by mait-aad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_point(t_data	*img, int x, int y)
{
	if(img->map[y / 80][x / 80] == '1')
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < img->img_w && img->img_h > y)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	put_wall(t_data	*img)
{
	int i;
	int	h;
	int w;
	
	i = 0;
	h = 0;
	while(h < 80)
	{
		w = 0;
		while (w < 80)
		{
			my_mlx_pixel_put(img, ((img->var.x * 80) + w) * img->mini_scall, ((img->var.y * 80) + h) * img->mini_scall , 0x27329F);
			i++;
			w++;
		}
		h++;
	}
}

void	put_ground(t_data	*img)
{
	int i;
	int	h;
	int w;
	
	i = 0;
	h = 0;
	while(h < 80)
	{
		w = 0;
		while (w < 80)
		{
			// if(w == 0 || h == 79)
			// 	my_mlx_pixel_put(img, (img->var.x * 80) + w, (img->var.y * 80) + h, 0x000000);
			// else
			my_mlx_pixel_put(img, ((img->var.x * 80) + w) * img->mini_scall, ((img->var.y * 80) + h) * img->mini_scall, 0xFFFFFF);
			i++;
			w++;
		}
		h++;
	}
}

void	put_myplayer(t_data *img)
{
	int i;
	int	h;
	int w;
	
	i = 0;
	h = 0;
	while(h < 10)
	{
		w = 0;
		while (w < 10)
		{
			my_mlx_pixel_put(img, (img->px + w) * img->mini_scall, (img->py + h) * img->mini_scall, 0xFF0000);
			i++;
			w++;
		}
		h++;
	}
}

int		haswallat(t_data	*img,int	x, int y)
{
	if(img->map[y / 80][x / 80] == '1')
		return(1);
	return (0);
}

void	normalizeangle(t_data	*img)
{
	img->rayangle =	remainder(img->rayangle, (2 * PI)); //c
	if (img->rayangle < 0)
		img->rayangle = (2 * PI) + img->rayangle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) 
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	raysfacing(t_data	*img)
{
	img->rayfacing.down = img->rayangle > 0 && img->rayangle < PI;
	img->rayfacing.up = !img->rayfacing.down;
	img->rayfacing.right = img->rayangle < (0.5 * PI) || img->rayangle > (1.5 * PI);
	img->rayfacing.left = !img->rayfacing.right;
}

void	horizontal_raygrid(t_data	*img, int	i)
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	img->rays[i].horzhitdistance = 0;
	yintercept = floor((img->py + 5) / 80) * 80;
	if(img->rayfacing.down)
		yintercept += 80;
	xintercept = img->px + 5 + (yintercept - img->py - 5) / tan(img->rayangle);
	ystep = 80;
	if(img->rayfacing.up)
		ystep *=  -1;
	xstep = 80	/ tan(img->rayangle);
	if(img->rayfacing.left && xstep > 0)
		xstep *=  -1;
	else if(img->rayfacing.right && xstep < 0)
		xstep *= -1;
	while(xintercept >= 0 && xintercept <= 80 * img->mapx && yintercept >= 0 && yintercept <= 80 * img->mapy)
	{
		if(img->rayfacing.up)
			yintercept -= 1;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rayfacing.up)
				++yintercept;
			img->rays[i].wallhitx = xintercept;
			img->rays[i].wallhity = yintercept;
			img->rays[i].horzhitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
			break;
		}
		else
		{
			if(img->rayfacing.up)
				yintercept += 1;
			xintercept += xstep;
			yintercept += ystep;
		}
	}
}

void	vertical_raygrid(t_data	*img, int i)
{
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;

	img->rays[i].verthitdistance = 0;
	xintercept = floor((img->px + 5) / 80) * 80;
	if(img->rayfacing.right)
		xintercept += 80;
	yintercept = img->py + 5 + (xintercept - img->px - 5) * tan(img->rayangle);
	xstep = 80;
	if(img->rayfacing.left)
		xstep *= -1;
	ystep = 80 * tan(img->rayangle);
	if(img->rayfacing.up && ystep > 0)
		ystep *=  -1;
	else if(img->rayfacing.down && ystep < 0)
		ystep *= -1; 
	while(xintercept >= 0 && xintercept <= 80 * img->mapx && yintercept >= 0 && yintercept <= 80 * img->mapy)
	{
		if(img->rayfacing.left)
			xintercept--;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rayfacing.left)
				++xintercept;
			img->rays[i].wallhitx = xintercept;
			img->rays[i].wallhity = yintercept;
			img->rays[i].verthitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
			break;
		}
		else
		{
			if(img->rayfacing.left)
				++xintercept;
			xintercept += xstep;
			yintercept += ystep;
		}
	}
}

void	cast(t_data	*img, int i)
{
	raysfacing(img);
	horizontal_raygrid(img, i);
	vertical_raygrid(img, i);
	if(!img->rays[i].verthitdistance)
	{
		img->rays[i].distance = img->rays[i].horzhitdistance;
		img->is_hor[i] = 1;
	}
	else if(!img->rays[i].horzhitdistance)
	{
		img->rays[i].distance = img->rays[i].verthitdistance;
		img->is_hor[i] = 0;
	}
	else if(img->rays[i].verthitdistance < img->rays[i].horzhitdistance)
		img->rays[i].distance = img->rays[i].verthitdistance;
	else if (img->rays[i].verthitdistance > img->rays[i].horzhitdistance)
		img->rays[i].distance = img->rays[i].horzhitdistance;
}

void	init_rays(t_data	*img)
{
	img->num_rays = (img->img_w / WALL_STRIP_WIDTH); 
	img->rayangle = img->rotationangle - (FOV_ANGLE / 2);
	if(!img->rays)
		img->rays = malloc(sizeof(t_cast) * img->num_rays);
	if(!img->is_hor)
		img->is_hor = malloc(sizeof(int) * img->num_rays);
}

void	castallrays(t_data	*img)
{
	int i = 0;
	int j;
	int x;
	int y;

	init_rays(img);
	while(i < img->num_rays)
	{
		j = 1;
		normalizeangle(img);
		cast(img, i);
		while(img->rays[i].distance > j)
		{
			x = img->px + 5 + cos(img->rayangle) * j;
			y = img->py + 5 + sin(img->rayangle) * j;
			my_mlx_pixel_put(img, x * img->mini_scall, y * img->mini_scall,	0x800080);
			j++;
		}
		img->rayangle += FOV_ANGLE / img->num_rays;
		img->rays[i].rayangle_pro = img->rayangle;
		i++;
	}
}
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void ft_react(t_data *data, int x, int y, int hight)
{
	int	j;
	int i;
	int	alpha;
	int coler;

	i = 0;
	while (i < WALL_STRIP_WIDTH)
	{		
		j = 0;
		while (j < hight)
		{
			if (y < 0)
				y = 0;
			if (x >= 0)
			{
				// if (data->is_hor[i] == 1)
				// 	coler = 200;
				// else
					coler = 255;
				alpha = 10700 / hight;
				my_mlx_pixel_put(data, x + i, y + j, create_trgb(10, coler, coler, coler));
				}
			j++;
		}
		i++;
	}
}

void rander_3dprojectedwall(t_data	*data)
{
	int i;
	int distance_projection_plan;
	int wall_hight;
	int correct_dest;

	i = 0;
	while(i < data->num_rays)
	{
		correct_dest = data->rays[i].distance * cos(data->rays[i].rayangle_pro - data->rotationangle);
		distance_projection_plan = (data->var.x * 80 / 2) / tan(FOV_ANGLE / 2);
		wall_hight = (int)((TILE_SIZE / ((double)correct_dest)) * ((double)distance_projection_plan));
		ft_react(data, i * WALL_STRIP_WIDTH, ((data->mapy * 80) /2) - (wall_hight / 2), wall_hight);
		i++;
	}
}

void	draw(t_data *img)
{
	img->var.y = 0;
	while (img->map[img->var.y])
	{
		img->var.x = 0;
		while (img->map[img->var.y][img->var.x])
		{
			if (img->map[img->var.y][img->var.x] == '1')
				put_wall(img);
			else if (img->map[img->var.y][img->var.x] == '0')
				put_ground(img);
			img->var.x++;
		}
		img->var.y++;
	}
	put_myplayer(img);
	castallrays(img);
	if (img->mini_scall != 1)
		rander_3dprojectedwall(img);
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
	img->mlx_win = mlx_new_window(img->mlx, img->mapx * 80, img->mapy * 80, "game");
	img->img = mlx_new_image(img->mlx, img->mapx * 80, img->mapy * 80);
	img->img_w =  img->mapx * 80;
	img->img_h =  img->mapy * 80;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}	