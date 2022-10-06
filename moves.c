#include "cub3d.h"


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
    if(keycode == 2)
		img->walkdirection2 = 1;
    else if(keycode == 0)
		img->walkdirection2 = -1;
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

void	update_direction1(t_data	*img)
{

	int px;
	int py;
	double	rotationangle;		


	rotationangle = img->rotationangle + (img->fov_angle * 1.5 * img->walkdirection2);
	img->movestep = img->movespeed;
	while(img->movestep >= 0)
	{
		px = (img->px + cos(rotationangle) * img->movestep);
		py = (img->py + sin(rotationangle) * img->movestep);
		if(img->map[py / TILE_SIZE][px / TILE_SIZE] == '0' && img->map[py / TILE_SIZE][(px + 10) / TILE_SIZE] == '0' && img->map[(py + 10) / TILE_SIZE][px / TILE_SIZE] == '0' && img->map[(py + 10) / TILE_SIZE][(px + 10) / TILE_SIZE] == '0')
		{
			img->px = px;
			img->py = py;
			return;
		}
		img->movestep--;
	}
}

void	update_direction0(t_data	*img)
{
	int	px;
	int py;

	while(img->movespeed >= 0)
	{
		img->movestep = img->walkdirection * img->movespeed;
		px = (img->px + cos(img->rotationangle) * img->movestep);
		py = (img->py + sin(img->rotationangle) * img->movestep);
		if(img->map[py / TILE_SIZE][px / TILE_SIZE] == '0' && img->map[py / TILE_SIZE][(px + 10) / TILE_SIZE] == '0' && img->map[(py + 10) / TILE_SIZE][px / TILE_SIZE] == '0' && img->map[(py + 10) / TILE_SIZE][(px + 10) / TILE_SIZE] == '0')
		{
			img->px = px;
			img->py = py;
			img->movespeed = 10;
			return ;
		}
		img->movespeed--;
	}
	img->movespeed = 10;
}

void	update(t_data	*img)
{
	img->rotationangle += img->turndirection * img->rotationspeed;
	if(img->walkdirection)
		update_direction0(img);
	if(img->walkdirection2)
		update_direction1(img);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 53 || keycode == 1 || keycode == 13)
		moves1(keycode, img);
	else if (keycode == 0 || keycode == 2)
		moves2 (keycode, img);
	else if(keycode == 123 || keycode == 124)
		moves3(keycode, img);
	else if(keycode == 48)
		img->minimap = 1;
	return (0);
}


int	key_hook2(int keycode, t_data *img)
{
	if(keycode == 1 || keycode == 13)
		img->walkdirection = 0;
	else if(keycode == 123 || keycode == 124)
		img->turndirection = 0;
	else if(keycode == 0 || keycode == 2)
		img->walkdirection2 = 0;
	else if(keycode == 46)
		img->mini_scall = 1;
	else if(keycode == 11)
		img->mini_scall = 0;
	else if(keycode == 48)
		img->minimap = 0;
	return (0);
}

int	loop_game(t_data	*img)
{
	update(img);
	if(img->img)
		mlx_destroy_image (img->mlx, img->img);
	mlx_clear_window (img->mlx, img->mlx_win);
	img->img = mlx_new_image(img->mlx,  W_WITHE, W_HIGHTE);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	draw(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	// mlx_destroy_image(img->mlx, img->s_textur_buffer.img);
	// mlx_destroy_image(img->mlx, img->n_textur_buffer.img);
	// mlx_destroy_image(img->mlx, img->e_textur_buffer.img);
	// mlx_destroy_image(img->mlx, img->w_textur_buffer.img);
	mlx_hook(img->mlx_win, 2, 1L, key_hook, img);
	mlx_hook(img->mlx_win, 3, 2L, key_hook2, img);
	return (0);
}

// void	draw(t_data *img)
// {
// 	img->var.y = 0;
// 	while (img->map[img->var.y])
// 	{
// 		img->var.x = 0;
// 		while (img->map[img->var.y][img->var.x])
// 		{
// 			if (img->map[img->var.y][img->var.x] == '1')
// 				put_wall(img);
// 			else if (img->map[img->var.y][img->var.x] == '0')
// 				put_ground(img);
// 			img->var.x++;
// 		}
// 		img->var.y++;
// 		while(img->var.x < img->g_w)
// 		{
// 			put_wall(img);
// 			img->var.x++;
// 		}
// 		img->var.y++;
// 	}
// 	put_myplayer(img);
// 	castallrays(img);
// 	if (img->mini_scall != 1)
// 		rander_3dprojectedwall(img);
// }

// void	castallrays(t_data	*img)
// {
// 	int i = 0;
// 	int j;
// 	int x;
// 	int y;

// 	init_rays(img);
// 	while(i < img->num_rays)
// 	{
// 		j = 1;
// 		normalizeangle(img);
// 		cast(img, i);
		
// 		while(img->rays[i].distance > j)
// 		{
// 			x = img->px + 5 + cos(img->rayangle) * j;
// 			y = img->py + 5 + sin(img->rayangle) * j;
// 			if (img->mini_scall == 1)
// 				my_mlx_pixel_put(img, x * img->mini_scall, y * img->mini_scall,	0x800080);
// 			j++;
// 		}
// 		img->rayangle += img->fov_angle / img->num_rays;
// 		img->rays[i].rayangle_pro = img->rayangle;
// 		i++;
// 	}
// }
