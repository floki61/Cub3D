#include "cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



void	find_player(t_player *player, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (img->map[i])
	{
		j = 0;
		while (img->map[i][j])
		{
			if (img->map[i][j] == 'P')
			{
				player->x = j;
				player->y = i;
				img->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
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

int		check_point(t_data	*img, int x, int y)
{
	if(img->map[y / 80][x / 80] == '1')
		return (0);
	return (1);
}

void	put_line(t_data *img)
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

void	put_myplayer2(t_data *img)
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

void	castallrays(t_data	*img)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	static int h;

	int		wall_strip_width = 1;
	int		num_rays = (img->mapx / wall_strip_width)  * 100; 
	double  fov_angle = 60 * (PI / 180);
	double	rayangle = img->rotationangle - (fov_angle / 2);

	if(h==1)
	{
		while(img->ray->lenght[i])
			printf("raylenght : %d\n", img->ray->lenght[i++]);
		i = 0;
		h = 2;
	}
	if(h==0)
	{
		printf("-raaaaaày\n");
		img->ray->lenght = malloc(sizeof(int) * num_rays);
		h = 1;
	}
	while(i < num_rays)
	{
		j = 0;
		while(1)
		{
			x = img->px + 5 + cos(rayangle) * j;
			y = img->py + 5 + sin(rayangle) * j;
			if(!check_point(img, x, y))
				break ;
			my_mlx_pixel_put(img, x, y,	0x800080);
			j++;
		}
		img->ray->lenght[i] = j;
		rayangle += fov_angle / num_rays;
		i++;
	}
	img->ray->lenght[i] = '\0';
	i = 0;
	// while(img->ray->lenght[i])
	// 	printf("raylenght : %d\n", img->ray->lenght[i++]);
	// exit (0);
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
	put_myplayer2(img);
	castallrays(img);
	put_line(img);
	// printf("redline : %d\n", img->ray->redline);
}

int	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

void	player_data(t_data *img)
{
	img->ray->redline = 0;
	img->walkdirection = 0;
	img->turndirection = 0;
	img->rotationangle = -PI / 2;
	img->rotationspeed = 2 * (PI / 180);
	img->movespeed = 10;
}

int	open_window(t_data *img)
{
	img->mapx = ft_strlen(img->map[0]);
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, img->mapx * 80, img->mapy * 80, "game");
	img->img = mlx_new_image(img->mlx, img->mapx * 80, img->mapy * 80);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	player_data(img);
	draw(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
	mlx_hook(img->mlx_win, 3, 2L, key_hook2, img);
	mlx_loop_hook(img->mlx, loop_game, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}