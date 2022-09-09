#include "cub3d.h"

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
			mlx_pixel_put(img->mlx, img->mlx_win, (img->var.x * 80) + w, (img->var.y * 80) + h, 0x000000);
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
				mlx_pixel_put(img->mlx, img->mlx_win, (img->var.x * 80) + w, (img->var.y * 80) + h, 0x000000);
			else
				mlx_pixel_put(img->mlx, img->mlx_win, (img->var.x * 80) + w, (img->var.y * 80) + h, 0xFFFFFF);
			i++;
			w++;
		}
		h++;
	}
}

void	put_line(t_data *img)
{
	float i;
	float x;
	float y;

	i = 0;
	
	while(i < 40)
	{
		x = img->px + 5 + cos(img->rotationangle) * i;
		y = img->py + sin(img->rotationangle) * i;
		mlx_pixel_put(img->mlx, img->mlx_win, x, y, 0xFF0000);
		i += 1;
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
			mlx_pixel_put(img->mlx, img->mlx_win, img->px + w, img->py + h, 0xFF0000);
			i++;
			w++;
		}
		h++;
	}
	put_line(img);
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
	img->indx++;
	ft_putstr (ft_itoa(img->indx));
}

int	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

void	player_data(t_data *img)
{
	img->walkdirection = 0;
	img->turndirection = 0;
	img->rotationangle = PI / 2;
	img->rotationspeed = 2 * (PI / 180);
	img->movespeed = 2;
}

int	open_window(t_data *img, t_node *var)
{
	int		x;
	int		y;

	x = ft_strlen(img->map[0]);
	y = var->lenght;
	img->indx = -1;
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, x * 80, y * 80, "game");
	player_data(img);
	draw(img);
	mlx_key_hook(img->mlx_win, key_hook, img);
	mlx_hook(img->mlx_win, 17, 0, destroy, img);
	mlx_loop(img->mlx);
	return (0);
}