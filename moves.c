#include "cub3d.h"

void	init_line(t_data *img)
{
	img->walkdirection = 0;
	img->turndirection = 0;
	img->ray->redline = 0;
}

void	moves3(int keycode, t_data *img)
{
	int	px;
	int	py;

	px = img->px;
	py = img->py;
    if(keycode == 123)
		img->turndirection = -1;
    else if(keycode == 124)
		img->turndirection = 1;
}

void	moves2(int keycode, t_data *img)
{
	int	px;
	int	py;

	px = img->px;
	py = img->py;
	printf("p : %d\n", img->map[(py / 80)][(px + 5) / 80])
    if(keycode == 2)
	{
		if(img->map[(py / 80)][(px + 5) / 80] == '0')
			img->px += 5;
	}
    else if(keycode == 0)
	{
		if(img->map[py / 80][(px - 5 ) /80] == '0')
			img->px -= 5;
	}
}

void	moves1(int keycode, t_data *img)
{
	int	px;
	int	py;

	px = img->px;
	py = img->py;
	if (keycode == 53)
		exit(0);
	else if(keycode == 1)
		img->walkdirection = -1;
    else if(keycode == 13)
		img->walkdirection = 1;
}

void	update(t_data	*img)
{
	int	px;
	int py;

	img->rotationangle += img->turndirection * img->rotationspeed;
	img->movestep = img->walkdirection * img->movespeed;
	px = (img->px + cos(img->rotationangle) * img->movestep);
	py = (img->py + sin(img->rotationangle) * img->movestep);
	if(img->map[py / 80][px / 80] == '1' || img->map[py / 80][(px + 10) / 80] == '1' || img->map[(py + 10) / 80][px / 80] == '1' || img->map[(py + 10) / 80][(px + 10) / 80] == '1')
		return ;
	img->px = img->px + cos(img->rotationangle) * img->movestep;
	img->py = img->py + sin(img->rotationangle) * img->movestep;
}

int	key_hook(int keycode, t_data *img)
{
	printf("keycode : %d\n",keycode);
	if (keycode == 53 || keycode == 1 || keycode == 13)
		moves1(keycode, img);
	else if (keycode == 0 || keycode == 2)
		moves2 (keycode, img);
	else if(keycode == 123 || keycode == 124)
		moves3(keycode, img);
	return (0);
}


int	key_hook2(int keycode, t_data *img)
{
	keycode = 0;
	init_line(img);
	return (0);
}

int	loop_game(t_data	*img)
{
	update(img);
	mlx_clear_window (img->mlx, img->mlx_win);
	img->img = mlx_new_image(img->mlx,  img->mapx* 80, img->mapy * 80);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	draw(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	init_line(img);
	return (0);
}