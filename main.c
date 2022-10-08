/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:34:24 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 03:21:06 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data	*img, char	*fd)
{
	img->rays = NULL;
	img->img = NULL;
	img->wall_textur = NULL;
	img->color_buff = NULL;
	img->walkdirection2 = 0;
	img->walkdirection = 0;
	img->fov_angle = (60 * (PI / 180));
	img->mini_scall = 0;
	img->color.index = 0;
	img->fd = open(fd, O_RDONLY);
	if (!(img->fd) || !img)
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data	img;

	check_name(argc, argv[1]);
	init_data(&img, argv[1]);
	read_map(&img);
    check_map(img.map, &img);
	open_window(&img);
}
