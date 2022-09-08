#include "cub3d.h"

void	init_line(t_data *img)
{
	img->walkdirection = 0;
	img->turndirection = 0;
}

void	moves2(int keycode, t_data *img)
{
	int	px;
	int	py;

	px = img->px;
	py = img->py;
    if(keycode == 2)
	{
		img->turndirection = 1;
        // img->px += 10;
	}
    else if(keycode == 1)
	{
		img->walkdirection = 1;
        img->py +=10;
	}
	img->rotationangle += img->turndirection * img->rotationspeed;

    mlx_clear_window (img->mlx, img->mlx_win);
	draw(img);
	put_myplayer2(img);
	init_line(img);
}

void	moves1(int keycode, t_data *img)
{
	int	px;
	int	py;

	px = img->px;
	py = img->py;
	if (keycode == 53)
		exit(0);
    if(keycode == 0)
	{
		img->turndirection = -1;
        // img->px -= 10;
	}
    else if(keycode == 13)
	{
		img->walkdirection = -1;
        img->py -= 10;
	}
	img->rotationangle += img->turndirection * img->rotationspeed;
	printf("rotation: %f\n", img->rotationangle);
    mlx_clear_window (img->mlx, img->mlx_win);
	draw(img);
	put_myplayer2(img);
	init_line(img);
	
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 53 || keycode == 0 || keycode == 13)
		moves1(keycode, img);
	else if (keycode == 1 || keycode == 2)
		moves2 (keycode, img);
	return (0);
}