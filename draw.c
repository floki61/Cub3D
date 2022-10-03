/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/03 15:23:02 by mait-aad         ###   ########.fr       */
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
			if (img->mini_scall == 1)
				my_mlx_pixel_put(img, ((img->var.x * 80) + w), ((img->var.y * 80) + h) , 0x27329F);
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
	while(h < 80)
	{
		w = 0;
		while (w < 80)
		{
			if((w == 0 || h == 79) && img->mini_scall == 1)
				my_mlx_pixel_put(img, ((img->var.x * 80) + w) , ((img->var.y * 80) + h) , 0x000000);
			else if (img->mini_scall == 1)
				my_mlx_pixel_put(img, ((img->var.x * 80) + w), ((img->var.y * 80) + h), 0xFFFFFF);
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
	while(h < 10)
	{
		w = 0;
		while (w < 10)
		{
			if (img->mini_scall == 1)
				my_mlx_pixel_put(img, (img->px + w), (img->py + h), 0xFF0000);
			w++;
		}
		h++;
	}
}

int		haswallat(t_data	*img,int	x, int y)
{	
	if (y / 80 >= img->mapy)
		return (1);
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

void	raysfacing(t_data	*img, int i)
{
	img->rays[i].rayfacing.down = img->rayangle > 0 && img->rayangle < PI;
	img->rays[i].rayfacing.up = !img->rays[i].rayfacing.down;
	img->rays[i].rayfacing.right = img->rayangle < (0.5 * PI) || img->rayangle > (1.5 * PI);
	img->rays[i].rayfacing.left = !img->rays[i].rayfacing.right;
}

void	horizontal_raygrid(t_data	*img, int	i)
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	img->rays[i].wallhity = 0;
	img->rays[i].horzhitdistance = 0;
	yintercept = floor((img->py + 5) / 80) * 80;
	if(img->rays[i].rayfacing.down)
		yintercept += 80;
	xintercept = img->px + 5 + (yintercept - img->py - 5) / tan(img->rayangle);
	ystep = 80;
	if(img->rays[i].rayfacing.up)
		ystep *= -1;
	xstep = 80	/ tan(img->rayangle);
	if(img->rays[i].rayfacing.left && xstep > 0)
		xstep *=  -1;
	else if(img->rays[i].rayfacing.right && xstep < 0)
		xstep *= -1;
	while(xintercept >= 0 && xintercept <= 80 * img->mapx && yintercept >= 0 && yintercept <= 80 * img->mapy)
	{
		if(img->rays[i].rayfacing.up)
			yintercept -= 1;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rays[i].rayfacing.up)
				++yintercept;
			img->rays[i].wallhitx = xintercept;
			img->rays[i].wallhity = yintercept;
			img->rays[i].horzhitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
			break;
		}
		else
		{
			if(img->rays[i].rayfacing.up)
				yintercept += 1;
			img->rays[i].horzhitdistance = 0;
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

	img->rays[i].wallhitx = 0;
	img->rays[i].wallhity = 0;
	img->rays[i].verthitdistance = 0;
	xintercept = floor((img->px + 5) / 80) * 80;
	if(img->rays[i].rayfacing.right)
		xintercept += 80;
	yintercept = img->py + 5 + (xintercept - img->px - 5) * tan(img->rayangle);
	xstep = 80;
	if(img->rays[i].rayfacing.left)
		xstep *= -1;
	ystep = 80 * tan(img->rayangle);
	if(img->rays[i].rayfacing.up && ystep > 0)
		ystep *=  -1;
	else if(img->rays[i].rayfacing.down && ystep < 0)
		ystep *= -1; 
	while(xintercept >= 0 && xintercept <= 80 * img->mapx && yintercept >= 0 && yintercept <= 80 * img->mapy)
	{
		if(img->rays[i].rayfacing.left)
			xintercept--;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rays[i].rayfacing.left)
				++xintercept;
			img->rays[i].wallhitx = xintercept;
			img->rays[i].wallhity = yintercept;
			img->rays[i].verthitdistance = distanceBetweenPoints(img->px + 5, img->py + 5, xintercept, yintercept);
			break;
		}
		else
		{
			if(img->rays[i].rayfacing.left)
				++xintercept;
			img->rays[i].verthitdistance = 0;
			xintercept += xstep;
			yintercept += ystep;
		}
	}
}

void	cast(t_data	*img, int i)
{
	raysfacing(img, i);
	horizontal_raygrid(img, i);
	vertical_raygrid(img, i);
	if(!img->rays[i].verthitdistance || (img->rays[i].verthitdistance > img->rays[i].horzhitdistance && img->rays[i].horzhitdistance))
	{
		img->rays[i].is_hor = 0;
		img->rays[i].distance = img->rays[i].horzhitdistance;
	}
	else if(!img->rays[i].horzhitdistance || img->rays[i].verthitdistance < img->rays[i].horzhitdistance)
	{
		img->rays[i].is_hor = 1;
		img->rays[i].distance = img->rays[i].verthitdistance;
	}
}

void	init_rays(t_data	*img)
{
	img->num_rays = (img->img_w/ WALL_STRIP_WIDTH); 
	img->rayangle = img->rotationangle - (FOV_ANGLE / 2);
	if(!img->rays)
		img->rays = malloc(sizeof(t_cast) * img->num_rays);
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
			if (img->mini_scall == 1)
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

void	pint_sc_gr(t_data *data, int top, int y, int x)
{
	int	i;

	i = -1;
	while(++i < top)
		*(unsigned int *)(data->addr + (i * data->line_length + x * (data->bits_per_pixel / 8))) = (unsigned int)0x85C1E9;
	i = y -1;
	while(data->img_h > ++i)
		*(unsigned int *)(data->addr + (i * data->line_length + x * (data->bits_per_pixel / 8))) = (unsigned int)0x95A5A6;
}

void ft_react(t_data *data, int x, int hight)
{
	int	j;
	int alpha;
	int	top_pixl;
	int	textureoffsetx;
	int bottem_pixl;
	int distancefromtop;
	int textureoffsety;

	top_pixl = (data->img_h/2) - (hight/2);
	top_pixl = top_pixl < 0 ? 0 : top_pixl;
	bottem_pixl = (data->img_h/2) + (hight/2);
	bottem_pixl = bottem_pixl >  data->img_h ? data->img_h : bottem_pixl;
	pint_sc_gr(data, top_pixl, bottem_pixl, x);
	if (data->rays[x].verthitdistance)
		textureoffsetx = (int)data->rays[x].wallhity % TEXTUR_HIGHT;
	else
		textureoffsetx = (int)data->rays[x].wallhitx % TEXTUR_WIDTH;
	j = top_pixl;
	while (j < bottem_pixl)
	{
		distancefromtop = j + (hight / 2) - (data->img_h / 2);
		textureoffsety = distancefromtop * TEXTUR_HIGHT / hight;
		alpha = 50;
		if (data->rays[x].is_hor == 1)
			alpha = 10;
		data->addr[j * data->line_length + x * (data->bits_per_pixel / 8)] = data->wall_textur[(TEXTUR_HIGHT * textureoffsety) + textureoffsetx];
		j++;
	}
}
void	ray_diriction(t_data	*data, int i)
{
	if (data->rays[i].is_hor)
	{
		if (data->rays[i].rayfacing.right)
			data->rays[i].dir = 'E';
		else if(data->rays[i].rayfacing.left)
			data->rays[i].dir = 'W';	
	}
	else if (data->rays[i].is_hor  == 2)
	{
		if (data->rays[i].rayfacing.down)
			data->rays[i].dir = 'S';
		else if (data->rays[i].rayfacing.up)
			data->rays[i].dir = 'N';
	}
}

void rander_3dprojectedwall(t_data *data)
{
	int i;
	int j;
	int distance_projection_plan;
	int wall_hight;
	int correct_dest;

	if (!data->wall_textur)
		data->wall_textur = (unsigned int *)malloc(sizeof(unsigned int) * TEXTUR_HIGHT * TEXTUR_WIDTH);
	i = -1;
	while (++i < TEXTUR_WIDTH)
	{
		j = -1;
		while (++j < TEXTUR_HIGHT)
			data->wall_textur[(TEXTUR_WIDTH * j) + i] = (i % 8 && j % 8) ?  create_trgb(100,0,0,255):create_trgb(255,0,0,0) ;
	}
	distance_projection_plan = (data->var.x * 80 / 2) / tan(FOV_ANGLE / 2);
	i = 0;
	while(i < data->num_rays)
	{
		// ray_diriction(data, i);
		correct_dest = data->rays[i].distance * cos(data->rays[i].rayangle_pro - data->rotationangle);
		wall_hight = (int)((TILE_SIZE / ((double)correct_dest)) * ((double)distance_projection_plan));
		ft_react(data, i, wall_hight);
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
	img->img_w =  img->mapx * 80;
	img->img_h =  img->mapy * 80;
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}	