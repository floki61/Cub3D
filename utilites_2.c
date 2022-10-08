/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilites_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:05:44 by mait-aad          #+#    #+#             */
/*   Updated: 2022/10/06 21:10:33 by mait-aad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_images(t_data	*d)
{
	d->n_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->n_path, &d->t_w, &d->t_h);
	d->s_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->s_path, &d->t_w, &d->t_h);
	d->e_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->e_path, &d->t_w, &d->t_h);
	d->w_textur_buffer.img
		= mlx_xpm_file_to_image(d->mlx, d->w_path, &d->t_w, &d->t_h);
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
