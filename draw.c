/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/18 03:58:46 by oel-berh         ###   ########.fr       */
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
		while (w < 79)
		{
			if(w == 0 || h == 79)
				my_mlx_pixel_put(img, (img->var.x * 80) + w, (img->var.y * 80) + h, 0x000000);
			else
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
	printf("rayanglenorm: %f\n",img->rays->rayangle);
	img->rays->rayangle =	fmod(img->rays->rayangle, (2 * PI));
	if (img->rays->rayangle < 0)
		img->rays->rayangle = (2 * PI) + img->rays->rayangle;
	printf("rayanglenorm2: %f\n",img->rays->rayangle);
}
void	cast(t_data	*img)
{
	int		xintercept;
	int		yintercept;
	int		xstep;
	int		ystep;
	int		israyfacingdown = 0;
	int		israyfacingup = 1;
	int		israyfacingright = 1;
	int		israyfacingleft = 1;
	
	if(img->rays->rayangle > 0 && img->rays->rayangle < PI)
		israyfacingdown = 80;
	printf("rayangle: %f\n", img->rays->rayangle);
	printf("hisfacingdown: %d\n", israyfacingdown);
	if(!israyfacingdown)
		israyfacingup = -1;
	printf("hisfacingup: %d\n", israyfacingup);
	if(img->rays->rayangle < (0.5 * PI) || img->rays->rayangle > (1.5 * PI))
		israyfacingright = -1;
	else
		israyfacingleft = -1;
		
	yintercept = (img->py / 80) * 80;
	yintercept += israyfacingdown; 
	
	xintercept = img->px + (yintercept - img->py) / tan(img->rays->rayangle);

	ystep = 80;
	ystep *= israyfacingup;

	xstep = 80	/ tan(img->rays->rayangle);
	if(israyfacingleft == -1 && ystep > 0)
		xstep *= israyfacingleft;
	if(israyfacingright == -1 && ystep < 0)
		xstep *= israyfacingright;

	int		nexthorztouchx = xintercept;
	int		nexthorztouchy = yintercept;
	
	if(israyfacingup == -1)
		nexthorztouchy--;
	while(1)
	{
		if(haswallat(img, nexthorztouchx, nexthorztouchy))
		{
			printf("hey\n");
			// int	foundhorzwallhit = 1;
			img->rays->wallhitx = nexthorztouchx;
			img->rays->wallhity = nexthorztouchy;
			break;
		}
		else
		{
			nexthorztouchx += xstep;
			nexthorztouchy += ystep;
		}
	}
	
}

void	init_rays(t_data	*img)
{
	img->rays->wall_strip_width = 1;
	img->rays->num_rays = (img->mapx / img->rays->wall_strip_width)  * 100; 
	img->rays->fov_angle = 60 * (PI / 180);
	img->rays->rayangle = img->rotationangle - (img->rays->fov_angle / 2);	
}
void	castallrays(t_data	*img)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	static int h;

	
	init_rays(img);
	printf("rotationangle§: %f\n", img->rotationangle);
	printf("rayangle befor cast§: %f\n", img->rays->rayangle);
	if(h==0)
	{
		img->ray->lenght = malloc(sizeof(int) * img->rays->num_rays);
		h = 1;
	}
	while(i < img->rays->num_rays)
	{
		j = 0;
		normalizeangle(img);
		printf("hey---------\n");
		cast(img);
		// while(x != img->rays->wallhitx && y != img->rays->wallhity)
		while(1)
		{
			x = img->px + 5 + cos(img->rays->rayangle) * j;
			y = img->py + 5 + sin(img->rays->rayangle) * j;
			
			printf("walhitx: %d\nwalhity: %d\n", img->rays->wallhitx, img->rays->wallhity);
			printf("x: %d\ny: %d\n", x, y);
			exit(0);
			if(!check_point(img, x, y))
				break ;
			my_mlx_pixel_put(img, x, y,	0x800080);
			j++;
		}
		img->ray->lenght[i] = j;
		img->rays->rayangle += img->rays->fov_angle / img->rays->num_rays;
		i++;
	}
	img->ray->lenght[i] = '\0';
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
	redray(img);
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
	draw(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}	