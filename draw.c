/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:59:04 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/05 21:49:19 by mait-aad         ###   ########.fr       */
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
	// exit(0);
	// int	x = ((img->mapx * TILE_SIZE) - (img->g_w * 20) - 10) + (img->var.x * 20);
	// int y = ((img->mapy * TILE_SIZE) - (img->mapy * 20) - 10) + (img->var.y * 20);
	while(h < 20)
	{
		w = 0;
		while (w < 20)
		{
			my_mlx_pixel_put(img, x + w, y + h, create_trgb(50, 220,120,120));
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
	// int x = ((img->mapx * TILE_SIZE) - (img->g_w * 20) - 10) + (img->var.x * 20);
	// int y = ((img->mapy * TILE_SIZE) - (img->mapy * 20) - 10) + (img->var.y * 20);
	while(h < 20)
	{
		w = 0;
		while (w < 20)
		{
			if(h == 19 || w == 19 )
				my_mlx_pixel_put(img, x + w, y + h , create_trgb(50, 120,120,120));
			else
				my_mlx_pixel_put(img, x + w, y + h, create_trgb(50, 255,255,255));
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
	int px = W_WITHE - (img->g_w * 20) - 10 + (img->px / 4);
	int py = W_HIGHTE - (img->mapy * 20) - 10 + (img->py / 4);
	// int	px = ((img->mapx * TILE_SIZE) - (img->g_w * 20) - 10) + (img->px / 4);;
	// int py = ((img->mapy * TILE_SIZE) - (img->mapy * 20) - 10) + (img->py / 4);
	while(h < 6)
	{
		w = 0;
		while (w < 6)
		{
			my_mlx_pixel_put(img, (px + w), (py + h), 0xFF0000);
			w++;
		}
		h++;
	}
}

int		haswallat(t_data	*img,int	x, int y)
{	
	if (y / TILE_SIZE >= img->mapy)
		return (1);
	if(img->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
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

	img->rays[i].horzhitdistance = 0;
	yintercept = floor((img->py + 5) / TILE_SIZE) * TILE_SIZE;
	if(img->rays[i].rayfacing.down)
		yintercept += TILE_SIZE;
	xintercept = img->px + 5 + (yintercept - img->py - 5) / tan(img->rayangle);
	ystep = TILE_SIZE;
	if(img->rays[i].rayfacing.up)
		ystep *= -1;
	xstep = TILE_SIZE	/ tan(img->rayangle);
	if(img->rays[i].rayfacing.left && xstep > 0)
		xstep *=  -1;
	else if(img->rays[i].rayfacing.right && xstep < 0)
		xstep *= -1;
	while(xintercept >= 0 && xintercept <= TILE_SIZE * img->mapx && yintercept >= 0 && yintercept <= TILE_SIZE * img->mapy)
	{
		if(img->rays[i].rayfacing.up)
			yintercept -= 1;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rays[i].rayfacing.up)
				++yintercept;
			img->rays[i].h_wallhitx = xintercept;
			img->rays[i].h_wallhity = yintercept;
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

	img->rays[i].verthitdistance = 0;
	xintercept = floor((img->px + 5) / TILE_SIZE) * TILE_SIZE;
	if(img->rays[i].rayfacing.right)
		xintercept += TILE_SIZE;
	yintercept = img->py + 5 + (xintercept - img->px - 5) * tan(img->rayangle);
	xstep = TILE_SIZE;
	if(img->rays[i].rayfacing.left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(img->rayangle);
	if(img->rays[i].rayfacing.up && ystep > 0)
		ystep *=  -1;
	else if(img->rays[i].rayfacing.down && ystep < 0)
		ystep *= -1; 
	while(xintercept >= 0 && xintercept <= TILE_SIZE * img->mapx && yintercept >= 0 && yintercept <= TILE_SIZE * img->mapy)
	{
		if(img->rays[i].rayfacing.left)
			xintercept--;
		if(haswallat(img,xintercept, yintercept))
		{
			if(img->rays[i].rayfacing.left)
				++xintercept;
			img->rays[i].v_wallhitx = xintercept;
			img->rays[i].v_wallhity = yintercept;
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
		img->rays[i].wallhitx = img->rays[i].h_wallhitx;
		img->rays[i].wallhity = img->rays[i].h_wallhitx;
		img->rays[i].distance = img->rays[i].horzhitdistance;
	}
	else if(!img->rays[i].horzhitdistance || img->rays[i].verthitdistance < img->rays[i].horzhitdistance)
	{
		img->rays[i].is_hor = 1;
		img->rays[i].wallhitx = img->rays[i].v_wallhity;
		img->rays[i].wallhity = img->rays[i].v_wallhity;
		img->rays[i].distance = img->rays[i].verthitdistance;
	}
}

void	init_rays(t_data	*img)
{
	img->num_rays = (W_WITHE/ WALL_STRIP_WIDTH); 
	img->rayangle = img->rotationangle - (FOV_ANGLE / 2);
	if(!img->rays)
		img->rays = malloc(sizeof(t_cast) * img->num_rays);
}


void	castallrays(t_data	*img)
{
	int i = 0;

	init_rays(img);
	while(i < img->num_rays)
	{
		normalizeangle(img);
		cast(img, i);
		// img->rays[i].raylenght = img->rays.distance;
		img->rays[i].rayangle_pro = img->rayangle;
		img->rayangle += FOV_ANGLE / img->num_rays;
		i++;
	}
}

void	pint_sc_gr(t_data *data, int top, int y, int x)
{
	int	i;

	i = -1;
	while(++i < top)
		*(unsigned int *)(data->addr + (i * data->line_length + x * (data->bits_per_pixel / 8))) = create_trgb(100, data->color.RedCeilling, data->color.GreenCeilling,data->color.BlueCeilling);
	i = y -1;
	while(W_HIGHTE > ++i)
		*(unsigned int *)(data->addr + (i * data->line_length + x * (data->bits_per_pixel / 8))) = create_trgb(100, data->color.RedFloor, data->color.GreenFloor,data->color.BlueFloor);
}

void ft_react(t_data *data, int x, int hight)
{
	int	j;
	int	top_pixl;
	int	textureoffsetx;
	int bottem_pixl;
	int distancefromtop;
	int textureoffsety;

	top_pixl = (W_HIGHTE/2) - (hight/2);
	top_pixl = top_pixl < 0 ? 0 : top_pixl;
	bottem_pixl = (W_HIGHTE/2) + (hight/2);
	bottem_pixl = bottem_pixl >  W_HIGHTE ? W_HIGHTE : bottem_pixl;
	pint_sc_gr(data, top_pixl, bottem_pixl, x);
	if (data->rays[x].verthitdistance)
		textureoffsetx = (int)data->rays[x].wallhity % TEXTUR_HIGHT;
	else
		textureoffsetx = (int)data->rays[x].wallhitx % TEXTUR_WIDTH;
	j = top_pixl;
	while (j < bottem_pixl)
	{

		distancefromtop = j + (hight / 2) - (W_HIGHTE / 2);
		textureoffsety = distancefromtop * TEXTUR_HIGHT / hight;
		if (data->rays[x].dir =='S')
			data->addr[j * data->line_length + x * data->bits_per_pixel / 8] = data->s_textur_buffer.addr[textureoffsety * data->s_textur_buffer.line_length + textureoffsetx * data->s_textur_buffer.bits_per_pixel / 8];
		else if (data->rays[x].dir == 'N')
			data->addr[j * data->line_length + x * data->bits_per_pixel / 8] = data->n_textur_buffer.addr[textureoffsety * data->n_textur_buffer.line_length + textureoffsetx * data->n_textur_buffer.bits_per_pixel / 8];
		else if (data->rays[x].dir == 'W')
			data->addr[j * data->line_length + x * data->bits_per_pixel / 8] = data->w_textur_buffer.addr[textureoffsety * data->w_textur_buffer.line_length + textureoffsetx * data->w_textur_buffer.bits_per_pixel / 8];
		else if (data->rays[x].dir == 'E')
			data->addr[(j * data->line_length )+ x * data->bits_per_pixel / 8] = data->e_textur_buffer.addr[textureoffsety * data->e_textur_buffer.line_length + textureoffsetx * data->e_textur_buffer.bits_per_pixel / 8];		
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
	int i;
	int distance_projection_plan;
	int wall_hight;
	int correct_dest;

	distance_projection_plan = (W_WITHE / 2) / tan(FOV_ANGLE / 2);
	i = 0;
	while(i < data->num_rays)
	{
		ray_diriction(data, i);
		correct_dest = data->rays[i].distance * cos(data->rays[i].rayangle_pro - data->rotationangle);
		wall_hight = (int)((TILE_SIZE / ((double)correct_dest)) * ((double)distance_projection_plan));
		ft_react(data, i, wall_hight);
		i++;
	}
}

void	drawrays(t_data	*img)
{
	int i = 0;
	int j;
	int x;
	int y;
	
	while(i < img->num_rays)
	{
		j = 1;
		while(img->rays[i].distance > j)
		{
			exit(0);
			x = img->px + 5 + cos(img->rays[i].rayangle_pro) * j;
			y = img->py + 5 + sin(img->rays[i].rayangle_pro) * j;
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
		// while(img->var.x < img->g_w)
		// {
		// 	put_wall(img);
		// 	img->var.x++;
		// }
		img->var.y++;
	}
	// put_myplayer(img);
	// drawrays(img);   
}

void	draw(t_data *img)
{
	castallrays(img);
	rander_3dprojectedwall(img);
	if(img->minimap)
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
	img->img_w =  img->mapx * TILE_SIZE;
	img->img_h =  img->mapy * TILE_SIZE;
	read_images(img);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}	