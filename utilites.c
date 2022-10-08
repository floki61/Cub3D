/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilites.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:15:29 by mait-aad          #+#    #+#             */
/*   Updated: 2022/10/07 16:27:29 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "cub3d.h"

void	pint_sc_gr(t_data *data, int top, int y, int x)
{
	int	i;

	i = -1;
	while (++i < top)
		*(unsigned int *)(data->addr
				+ (i * data->line_length + x * (data->bits_per_pixel / 8)))
			= create_trgb(100, data->color.redceilling,
				data->color.greenceilling, data->color.blueceilling);
	i = y -1;
	while (W_HIGHTE > ++i)
		*(unsigned int *)(data->addr
				+ (i * data->line_length + x * (data->bits_per_pixel / 8)))
			= create_trgb(100, data->color.redfloor,
				data->color.greenfloor, data->color.bluefloor);
}

int	x_ofset(t_data *data, int x)
{
	int	i;

	if (data->rays[x].verthitdistance)
		i = (int)data->rays[x].wallhity % TEXTUR_HIGHT;
	else
		i = (int)data->rays[x].wallhitx % TEXTUR_WIDTH;
	return (i);
}

void	draw_the_3d(t_data	*data, int addr_index, int texture_index, int x)
{
	if (data->rays[x].dir == 'S')
		*(unsigned int *)(data->addr + addr_index)
			= data->s_textur_buffer.addr[texture_index];
	else if (data->rays[x].dir == 'N')
		*(unsigned int *)(data->addr + addr_index)
			= data->n_textur_buffer.addr[texture_index];
	else if (data->rays[x].dir == 'W')
		*(unsigned int *)(data->addr + addr_index)
			= data->w_textur_buffer.addr[texture_index];
	else if (data->rays[x].dir == 'E')
		*(unsigned int *)(data->addr + addr_index)
			= data->e_textur_buffer.addr[texture_index];
}

int	get_top(int hight)
{
	int	top_pixl;

	top_pixl = (W_HIGHTE / 2) - (hight / 2);
	if (top_pixl < 0)
		return (0);
	else
		return (top_pixl);
}

int	get_bottem(int hight)
{
	int	bottem_pixl;

	bottem_pixl = (W_HIGHTE / 2) + (hight / 2);
	if (bottem_pixl > W_HIGHTE)
		return (W_HIGHTE);
	else
		return (bottem_pixl);
}
