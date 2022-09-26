/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/27 00:54:27 by oel-berh         ###   ########.fr       */
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
			my_mlx_pixel_put(img, ((img->var.x * 80) + w) * 0.2, ((img->var.y * 80) + h) * 0.2 , 0x27329F);
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
		while (w < 79)
		{
			if(w == 0 || h == 79)
				my_mlx_pixel_put(img, ((img->var.x * 80) + w) * 0.2, ((img->var.y * 80) + h) * 0.2, 0x000000);
			else
				my_mlx_pixel_put(img, ((img->var.x * 80) + w) * 0.2, ((img->var.y * 80) + h) * 0.2, 0xFFFFFF);
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
			my_mlx_pixel_put(img, (img->px + w) * 0.2, (img->py + h) * 0.2, 0xFF0000);
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
	img->rays.rayangle =	remainder(img->rays.rayangle, (2 * PI)); //c
	if (img->rays.rayangle < 0)
		img->rays.rayangle = (2 * PI) + img->rays.rayangle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) 
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	raysfacing(t_data	*img)
{
	img->rayfacing.down = img->rays.rayangle > 0 && img->rays.rayangle < PI;
	img->rayfacing.up = !img->rayfacing.down;
	img->rayfacing.right = img->rays.rayangle < (0.5 * PI) || img->rays.rayangle > (1.5 * PI);
	img->rayfacing.left = !img->rayfacing.right;
}

void	horizontal_raygrid(t_data	*img)
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	img->rays.horzhitdistance = 0;
	yintercept = floor((img->py + 5) / 80) * 80;
	if(img->rayfacing.down)
		yintercept += 80;
	xintercept = img->px + 5 + (yintercept - img->py - 5) / tan(img->rays.rayangle);
	ystep = 80;
	if(img->rayfacing.up)
		ystep *=  -1;
	xstep = 80	/ tan(img->rays.rayangle);
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
			img->rays.wallhitx = xintercept;
			img->rays.wallhity = yintercept;
			img->rays.horzhitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
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

void	vertical_raygrid(t_data	*img)
{
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;

	img->rays.verthitdistance = 0;
	xintercept = floor((img->px + 5) / 80) * 80;
	if(img->rayfacing.right)
		xintercept += 80;
	yintercept = img->py + 5 + (xintercept - img->px - 5) * tan(img->rays.rayangle);
	xstep = 80;
	if(img->rayfacing.left)
		xstep *= -1;
	ystep = 80 * tan(img->rays.rayangle);
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
			img->rays.wallhitx = xintercept;
			img->rays.wallhity = yintercept;
			img->rays.verthitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
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

void	cast(t_data	*img)
{
	raysfacing(img);
	horizontal_raygrid(img);
	vertical_raygrid(img);
	if(!img->rays.verthitdistance)
		img->rays.distance = img->rays.horzhitdistance;
	else if(!img->rays.horzhitdistance)
		img->rays.distance = img->rays.verthitdistance;
	else if(img->rays.verthitdistance < img->rays.horzhitdistance)
	{
		img->rays.distance = img->rays.verthitdistance;
	}
	else if (img->rays.verthitdistance > img->rays.horzhitdistance)
	{
		img->rays.distance = img->rays.horzhitdistance;
	}
}

void	init_rays(t_data	*img)
{
	img->rays.num_rays = (img->img_w / WALL_STRIP_WIDTH); 
	img->rays.rayangle = img->rotationangle - (FOV_ANGLE / 2);
	if(!img->rays.raylenght)
		img->rays.raylenght = malloc(sizeof(int) * img->rays.num_rays);
	if(!img->rays.rayangle_pro)
		img->rays.rayangle_pro = malloc(sizeof(double) * img->rays.num_rays);
}

void	castallrays(t_data	*img)
{
	int i = 0;

	init_rays(img);
	while(i < img->rays.num_rays)
	{
		normalizeangle(img);
		cast(img);
		img->rays.raylenght[i] = img->rays.distance;
		img->rays.rayangle_pro[i] = img->rays.rayangle;
		img->rays.rayangle += FOV_ANGLE / img->rays.num_rays;
		i++;
	}
	// img->rays.raylenght[i] = '\0';
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void ft_react(t_data *data, int x, int y, int hight)
{
	int	i;
	int	j;
	int	alpha;

			
	j = 0;
	i = -1;
	while(y > i++)
		my_mlx_pixel_put(data, x, i, 0x85C1E9);
	i = y + hight - 1;
	while(++i < data->mapy * 80)
		my_mlx_pixel_put(data,  x, i, 0x95A5A6);
	while (j < hight)
	{
		if (y < 0)
			y = 0;
		if (x >= 0)
		{
			alpha = 10700 / hight;
			my_mlx_pixel_put(data, x, y + j, create_trgb(alpha, 255, 255, 255));
		}
		j++;
	}
}

void rander_3dprojectedwall(t_data	*data)
{
	int i;
	int distance_projection_plan;
	int wall_hight;
	int correct_dest;

	i = 0;
	while(i < data->rays.num_rays)
	{	
		correct_dest = data->rays.raylenght[i] * cos(data->rays.rayangle_pro[i] - data->rotationangle);
		distance_projection_plan = (data->var.x * 80 / 2) / tan(FOV_ANGLE / 2);
		wall_hight = (int)((TILE_SIZE / ((double)correct_dest)) * ((double)distance_projection_plan));
		ft_react(data, i * WALL_STRIP_WIDTH, ((data->mapy * 80) /2) - (wall_hight / 2), wall_hight);
		i++;
	}
}

void	drawrays(t_data	*img)
{
	int i = 0;
	int j;
	int x;
	int y;
	
	while(i < img->rays.num_rays)
	{
		j = 1;
		while(img->rays.raylenght[i] > j)
		{
			x = img->px + 5 + cos(img->rays.rayangle_pro[i]) * j;
			y = img->py + 5 + sin(img->rays.rayangle_pro[i]) * j;
			my_mlx_pixel_put(img, x * 0.2, y * 0.2,	0x800080);
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
			if(img->map[img->var.y][img->var.x] == '1')
				put_wall(img);
			else if (img->map[img->var.y][img->var.x] == ' ' || img->map[img->var.y][img->var.x] == '\t')
				put_wall(img);
			else if (img->map[img->var.y][img->var.x] == '0')
				put_ground(img);
			img->var.x++;
		}
		while(img->var.x < img->g_w)
		{
			put_wall(img);
			img->var.x++;
		}
		img->var.y++;
	}
	put_myplayer(img);
	// drawrays(img);
}

void	draw(t_data *img)
{
	castallrays(img);
	rander_3dprojectedwall(img);
	if(img->drawmap)
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
	img->mlx_win = mlx_new_window(img->mlx, img->mapx * 80, img->mapy * 80, "game");
	// img->img = mlx_new_image(img->mlx, img->mapx * 80, img->mapy * 80);
	img->img_w =  img->mapx * 80;
	img->img_h =  img->mapy * 80;
	// img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}	