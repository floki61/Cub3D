/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:42:57 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 03:34:14 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

void	free_tab(char	**str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
}

int	set_path(t_data *img, char	*identifier, char	*path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == 1)
		return (0);
	if (!strcmp(identifier, "NO") && img->path.index == 0)
		img->n_path = path;
	else if (!strcmp(identifier, "SO") && img->path.index == 1)
		img->s_path = path;
	else if (!strcmp(identifier, "WE") && img->path.index == 2)
		img->w_path = path;
	else if (!strcmp(identifier, "EA") && img->path.index == 3)
		img->e_path = path;
	else
		return (0);
	return (1);
}

int	path_texture(t_data *img, char	*path)
{
	char	**str;

	if (!strcmp(path, "\n"))
		return (0);
	str = ft_split(path, ' ');
	if (str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if (!set_path(img, str[0], str[1]))
		{
			printf("--------ERROR--------\n");
			exit (0);
		}
		img->path.index++;
	}
	return (0);
}

int	is_num(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' && str[i] > '9')
			return (0);
	return (1);
}

void	setcolor(t_data *img, int color, int c, int i)
{
	if (i == 0 && c == 'f')
		img->color.redfloor = color;
	else if (i == 0 && c == 'c')
		img->color.redceilling = color;
	else if (i == 1 && c == 'f')
		img->color.greenfloor = color;
	else if (i == 1 && c == 'c')
		img->color.greenceilling = color;
	else if (i == 2 && c == 'f')
		img->color.bluefloor = color;
	else if (i == 2 && c == 'c')
		img->color.blueceilling = color;
	else
	{
		printf("kkk\n");
		exit(0);
	}
}

int	check_color(char *color)
{
	int	ncolor;

	if (is_num(color))
	{
		ncolor = atoi(color);
		if (ncolor >= 0 && ncolor <= 255)
			return (ncolor);
	}
	printf("--------ERROR--------\n");
	exit (0);
}

int	ceilling_color(t_data *img, char	*value, int c)
{
	char	**color_tab;
	int		i;

	i = -1;
	color_tab = ft_split(value, ',');
	if (color_tab[2] && !color_tab[3])
	{
		while (color_tab[++i])
			setcolor(img, check_color(color_tab[i]), c, i);
	}
	else
	{
		printf("--------ERROR--------\n");
		exit (0);
	}
	img->color.index += 1;
	free_tab(color_tab);
	return (i);
}

int	set_color(t_data *img, char	*path)
{
	char	**str;

	if (!strcmp(path, "\n"))
		return (0);
	str = ft_split(path, ' ');
	if (str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if (!strcmp(str[0], "F") && img->color.index == 0)
			ceilling_color(img, str[1], 'f');
		else if (!strcmp(str[0], "C") && img->color.index == 1)
			ceilling_color(img, str[1], 'c');
		else
		{
			free_tab(str);
			printf("--------ERROR--------\n");
			exit (0);
		}
	}
	free_tab(str);
	return (0);
}

void	read_map(t_data *img)
{
	char	*instruction;
	char	*tab;

	instruction = get_next_line(img->fd);
	tab = NULL;
	if (!instruction)
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	while (instruction)
	{
		if (img->path.index < 4)
			path_texture(img, instruction);
		else if (img->color.index < 2)
			set_color(img, instruction);
		else
			tab = ft_strjoin(tab, instruction);
		free(instruction);
		instruction = get_next_line(img->fd);
	}
	free(instruction);
	img->map = ft_split(tab, '\n');
	free(tab);
	return ;
}
