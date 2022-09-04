#include "cub3d.h"


void	moves3(t_data *img, int py, int px)
{
	if (img->map[py][px] == 'C')
		img->c--;
	if (img->map[py][px] == 'E' && img->c == 0)
	{
		ft_putstr("9BIII7");
		exit (0);
	}
	else if (img->map[py][px] == 'E')
		return ;
	img->map[img->py][img->px] = '0';
	img->map[py][px] = 'P';
	mlx_clear_window (img->mlx, img->mlx_win);
	// draw (img);
}


void	moves2(int keycode, t_data *img)
{
	int	px;
	int	py;

	px = img->px;
	py = img->py;

    if(keycode == 2)
        img->px += 10;
    else if(keycode == 1)
        img->py +=10;
    mlx_clear_window (img->mlx, img->mlx_win);
	draw (img);
	// if (keycode == 1 && img->map[py + 1][px] != '1')
	// {
	// 	img->p_p = 1;
	// 	py++;
	// }
	// else if (keycode == 2 && img->map[py][px + 1] != '1')
	// {
	// 	img->p_p = 2;
	// 	px++;
	// }
	// moves3 (img, py, px);
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
        img->px -= 10;
    else if(keycode == 13)
        img->py -= 10;
    mlx_clear_window (img->mlx, img->mlx_win);
	draw (img);
	// else if (keycode == 0 && img->map[py][px - 1] != '1')
	// {
	// 	img->p_p = 3;
	// 	px--;
	// }
	// else if (keycode == 13 && img->map[py - 1][px] != '1')
	// {
	// 	img->p_p = 4;
	// 	py--;
	// }
	// moves3 (img, py, px);
}

int	key_hook(int keycode, t_data *img)
{
	// search_map(img, 'P');
	if (keycode == 53 || keycode == 0 || keycode == 13)
		moves1(keycode, img);
	else if (keycode == 1 || keycode == 2)
		moves2 (keycode, img);
	return (0);
}