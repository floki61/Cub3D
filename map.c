/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:42:57 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/11 03:45:27 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_path(t_data *img, char	*identifier, char	*path)
{
	int	fd;

	if (!strcmp(identifier, "NO") || !strcmp(identifier, "SO")
		|| !strcmp(identifier, "WE")
		|| !strcmp(identifier, "EA"))
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
		{
			printf("ERROR: invalide path\n");
			exit(0);
		}
		if (!strcmp(identifier, "NO") && !img->n_path)
			img->n_path = path;
		else if (!strcmp(identifier, "SO") && !img->s_path)
			img->s_path = path;
		else if (!strcmp(identifier, "WE") && !img->w_path)
			img->w_path = path;
		else if (!strcmp(identifier, "EA") && !img->e_path)
			img->e_path = path;
	}
	else
		return (0);
	return (1);
}

int	set_color(t_data *img, char	*value, int c)
{
	char	**color_tab;
	int		i;

	i = -1;
	color_tab = ft_split(value, ',');
	if (color_tab[2] && !color_tab[3])
	{
		while (color_tab[++i])
			check_color(color_tab[i]);
		init_color(img, color_tab, c);
	}
	else
	{
		printf("--------ERROR IN COLOR--------\n");
		exit (0);
	}
	img->color.index += 1;
	free_tab(color_tab);
	return (1);
}

int	element_map(t_data *img, char	*path)
{
	char	**str;

	if (!strcmp(path, "\n"))
		return (1);
	str = ft_split(path, ' ');
	if (str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if (set_path(img, str[0], str[1]))
			img->path.index++;
		else if (!strcmp(str[0], "F") && img->color.findex == 0)
			set_color(img, str[1], 'f');
		else if (!strcmp(str[0], "C") && img->color.cindex == 0)
			set_color(img, str[1], 'c');
		else
		{
			free_tab(str);
			printf("-------- IN COLOR--------\n");
			exit (0);
		}
	}
	free (str[0]);
	return (1);
}

void	nline(char *map)
{
	int	i;

	i = 0;
	while (map[i] == '\n')
		i++;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			exit (0);
		i++;
	}
	return ;
}

void	read_map(t_data *img)
{
	char	*instruction;
	char	*tab;

	instruction = get_next_line(img->fd);
	tab = NULL;
	if (!instruction)
	{
		printf("Error EMPTY FILE\n");
		exit (0);
	}
	while (instruction)
	{
		if (img->path.index < 4 || img->color.index < 2)
			element_map(img, instruction);
		else
			tab = ft_strjoin(tab, instruction);
		free(instruction);
		instruction = get_next_line(img->fd);
	}
	free(instruction);
	nline(tab);
	img->map = ft_split(tab, '\n');
	free(tab);
	return ;
}
