/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/22 02:40:55 by oel-berh         ###   ########.fr       */
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

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
			my_mlx_pixel_put(img, (img->var.x * 80) + w, (img->var.y * 80) + h, 0x27329F);
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
			my_mlx_pixel_put(img, (img->var.x * 80) + w, (img->var.y * 80) + h, 0xFFFFFF);
			i++;
			w++;
		}
		h++;
	}
}


void	redray(t_data *img)
{
	int x;
	int y;

	while(1)
	{
		x = img->px + 5 + cos(img->rotationangle) * img->ray->redline;
		y = img->py + 5 + sin(img->rotationangle) * img->ray->redline;
		if(!check_point(img, x, y))
			return ;
		my_mlx_pixel_put(img, x, y, 0xFF0000);
		img->ray->redline++;
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
			my_mlx_pixel_put(img, img->px + w, img->py + h, 0xFF0000);
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
	img->rays->rayangle =	remainder(img->rays->rayangle, (2 * PI)); //c
	if (img->rays->rayangle < 0)
		img->rays->rayangle = (2 * PI) + img->rays->rayangle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) 
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	raysfacing(t_data	*img)
{
	img->rayfacing->down = img->rays->rayangle > 0 && img->rays->rayangle < PI;
	img->rayfacing->up = !img->rayfacing->down;
	img->rayfacing->right = img->rays->rayangle < (0.5 * PI) || img->rays->rayangle > (1.5 * PI);
	img->rayfacing->left = !img->rayfacing->right;
}

void	horizontal_raygrid(t_data	*img)
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	img->rays->horzhitdistance = 0;
	yintercept = floor((img->py + 5) / 80) * 80;
	if(img->rayfacing->down)
		yintercept += 80;
	xintercept = img->px + 5 + (yintercept - img->py - 5) / tan(img->rays->rayangle);
	ystep = 80;
	if(img->rayfacing->up)
		ystep *=  -1;
	xstep = 80	/ tan(img->rays->rayangle);
	if(img->rayfacing->left && xstep > 0)
		xstep *=  -1;
	else if(img->rayfacing->right && xstep < 0)
		xstep *= -1;
	while(xintercept >= 0 && xintercept <= 80 * img->mapx && yintercept >= 0 && yintercept <= 80 * img->mapy)
	{
		if(img->rayfacing->up)
			yintercept -= 1;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rayfacing->up)
				++yintercept;
			img->rays->wallhitx = xintercept;
			img->rays->wallhity = yintercept;
			img->rays->horzhitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
			break;
		}
		else
		{
			if(img->rayfacing->up)
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

	img->rays->verthitdistance = 0;
	xintercept = floor((img->px + 5) / 80) * 80;
	if(img->rayfacing->right)
		xintercept += 80;
	yintercept = img->py + 5 + (xintercept - img->px - 5) * tan(img->rays->rayangle);
	xstep = 80;
	if(img->rayfacing->left)
		xstep *= -1;
	ystep = 80 * tan(img->rays->rayangle);
	if(img->rayfacing->up && ystep > 0)
		ystep *=  -1;
	else if(img->rayfacing->down && ystep < 0)
		ystep *= -1; 
	while(xintercept >= 0 && xintercept <= 80 * img->mapx && yintercept >= 0 && yintercept <= 80 * img->mapy)
	{
		if(img->rayfacing->left)
			xintercept--;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rayfacing->left)
				++xintercept;
			img->rays->wallhitx = xintercept;
			img->rays->wallhity = yintercept;
			img->rays->verthitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
			break;
		}
		else
		{
			if(img->rayfacing->left)
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
	if(!img->rays->verthitdistance)
		img->rays->distance = img->rays->horzhitdistance;
	else if(!img->rays->horzhitdistance)
		img->rays->distance = img->rays->verthitdistance;
	else if(img->rays->verthitdistance < img->rays->horzhitdistance)
	{
		img->rays->distance = img->rays->verthitdistance;
	}
	else if (img->rays->verthitdistance > img->rays->horzhitdistance)
	{
		img->rays->distance = img->rays->horzhitdistance;
	}
}

void	init_rays(t_data	*img)
{
	img->rays->num_rays = (img->mapx / wall_strip_width); 
	img->rays->rayangle = img->rotationangle - (fov_angle / 2);
	if(!img->rays->raylenght)
		img->rays->raylenght = malloc(sizeof(int) * img->rays->num_rays);
}

void	castallrays(t_data	*img)
{
	int i = 0;
	int j;
	int x;
	int y;

	init_rays(img);
	while(i < img->rays->num_rays)
	{
		j = 1;
		normalizeangle(img);
		cast(img);
		while(img->rays->distance > j)
		{
			x = img->px + 5 + cos(img->rays->rayangle) * j;
			y = img->py + 5 + sin(img->rays->rayangle) * j;
			my_mlx_pixel_put(img, x, y,	0x800080);
			j++;
		}
		img->rays->raylenght[i] = img->rays->distance;
		img->rays->rayangle += fov_angle / img->rays->num_rays;
		i++;
	}
	img->rays->raylenght[i] = '\0';
	
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
	// redray(img);
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
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	// draw(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}	