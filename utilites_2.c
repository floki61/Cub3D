/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilites_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:05:44 by mait-aad          #+#    #+#             */
/*   Updated: 2022/10/23 20:46:10 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture(t_data *d)
{
	d->n_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->n_path, &d->t_w, &d->t_h);
	d->s_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->s_path, &d->t_w, &d->t_h);
	d->e_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->e_path, &d->t_w, &d->t_h);
	d->w_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->w_path, &d->t_w, &d->t_h);
	if (!d->e_textur_buffer.img || !d->n_textur_buffer.img
		|| !d->s_textur_buffer.img || !d->w_textur_buffer.img)
	{
		write(2, "textur problem\n", 15);
		exit(0);
	}
}

void	norm_1(char	**str)
{
	free_tab(str);
	printf("--------element-map Error--------\n");
	exit (0);
}

void	make_b_image(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < W_WITHE)
	{
		j = 0;
		while (j < W_HIGHTE)
		{
			*(unsigned int *)(data->addr
					+ (j * data->line_length + i * (data->bits_per_pixel / 8)))
				= 0;
			j++;
		}
		i++;
	}
}

void	read_images(t_data	*d)
{
	check_texture(d);
	d->n_textur_buffer.addr
		= (unsigned int*)mlx_get_data_addr(d->n_textur_buffer.img,
			&d->n_textur_buffer.bits_per_pixel,
			&d->n_textur_buffer.line_length, &d->n_textur_buffer.endian);
	d->s_textur_buffer.addr
		= (unsigned int*)mlx_get_data_addr(d->s_textur_buffer.img,
			&d->s_textur_buffer.bits_per_pixel,
			&d->s_textur_buffer.line_length, &d->s_textur_buffer.endian);
	d->e_textur_buffer.addr
		= (unsigned int*)mlx_get_data_addr(d->e_textur_buffer.img,
			&d->e_textur_buffer.bits_per_pixel,
			&d->e_textur_buffer.line_length, &d->e_textur_buffer.endian);
	d->w_textur_buffer.addr
		= (unsigned int*)mlx_get_data_addr(d->w_textur_buffer.img,
			&d->w_textur_buffer.bits_per_pixel,
			&d->w_textur_buffer.line_length, &d->w_textur_buffer.endian);
}
