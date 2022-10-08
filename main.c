/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:34:24 by oel-berh          #+#    #+#             */
/*   Updated: 2022/10/08 03:21:06 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
=======
/*   By: mait-aad <mait-aad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:25:53 by mait-aad          #+#    #+#             */
/*   Updated: 2022/10/06 22:25:54 by mait-aad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	no_path(t_data *img, char	*identifier, char	*path)
{
	if (!strcmp(identifier, "NO"))
	{	
		img->n_path = path;
		img->path.no = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.no);
	}
	return (-1);
}

int	so_path(t_data *img, char	*identifier, char	*path)
{
	if (!strcmp(identifier, "SO"))
	{	
		img->s_path = path;
		img->path.so = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.so);
	}
	return (-1);
}

int	we_path(t_data *img, char	*identifier, char	*path)
{
	if (!strcmp(identifier, "WE"))
	{	
		img->w_path = path;
		img->path.we = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.we);
	}
	return (-1);
}

int	ea_path(t_data *img, char	*identifier, char	*path)
{
	if (!strcmp(identifier, "EA"))
	{	
		img->e_path = path;
		img->path.ea = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.ea);
	}
	return (-1);
}

void	free_tab(char	**str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
}

int	path_texture(t_data *img, char	*path)
{
	char	**str;
	int		ret;

	ret = 0;
	str = ft_split(path, ' ');
	if (str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if (img->path.index == 0)
			ret = no_path(img, str[0], str[1]);
		else if (img->path.index == 1)
			ret = so_path(img, str[0], str[1]);
		else if (img->path.index == 2)
			ret = we_path(img, str[0], str[1]);
		else if (img->path.index == 3)
			ret = ea_path(img, str[0], str[1]);
		// free_tab(str);
		if (ret != -1)
			return (1);
	}
	printf("--------ERROR--------\n");
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

int	FLOOR_COLOR(t_data *img, char	*value)
{
	int		i;
	int		color;
	char	**color_tab;

	i = 0;
	color_tab = ft_split(value, ',');
	if (color_tab[2] && !color_tab[3])
	{	
		while (color_tab[i])
		{
			if (is_num(color_tab[i]))
			{
				color = atoi(color_tab[i]);
				if (color >= 0 && color <= 255)
				{
					if (i == 0)
						img->color.redfloor = color;
					else if (i == 1)
						img->color.greenfloor = color;
					else if (i == 2)
						img->color.bluefloor = color;
				}
				else
					break ;
				i++;
			}
			else
				break ;
		}
		if (i == 3)
			img->color.index += 1;
	}
	free_tab(color_tab);
	return (i);
}

int	CEILLING_COLOR(t_data *img, char	*value)
{
	int		i;
	int		color;
	char	**color_tab;

	i = 0;
	color_tab = ft_split(value, ',');
	if (color_tab[2] && !color_tab[3])
	{	
		while (color_tab[i])
		{
			if (is_num(color_tab[i]))
			{
				color = atoi(color_tab[i]);
				if (color >= 0 && color <= 255)
				{
					if (i == 0)
						img->color.redceilling = color;
					else if (i == 1)
						img->color.greenceilling = color;
					else if (i == 2)
						img->color.blueceilling = color;
				}
				else
					break ;
				i++;
			}
			else
				break ;
		}
		if (i == 3)
			img->color.index += 1;
	}
	free_tab(color_tab);
	return (i);
}

int	set_color(t_data *img, char	*path)
{
	char	**str;
	int		ret;

	ret = -1;
	str = ft_split(path, ' ');
	if (str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if (img->color.index == 0 && !strcmp(str[0], "F"))
			ret = FLOOR_COLOR(img, str[1]);
		else if (img->color.index == 1 && !strcmp(str[0], "C"))
			ret = CEILLING_COLOR(img, str[1]);
		free_tab(str);
		if (ret == 3)
			return (1);
	}
	printf("--------ERROR--------\n");
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
		{	
			if (strcmp(instruction, "\n"))
				if (!path_texture(img, instruction))
					exit (0);
		}
		else if (img->color.index < 2)
		{
			if (strcmp(instruction, "\n"))
				if (!set_color(img, instruction))
					exit(0);
		}
		else
			tab = ft_strjoin(tab, instruction);
		free(instruction);
		instruction = get_next_line(img->fd);
	}
	free(instruction);
	img->map = ft_split(tab, '\n');
	free(tab);
	if (!check_map(img->map, img))
	{
		ft_putstr("Error Invalide Map\n");
		exit (0);
	}
	return ;
}
>>>>>>> 2693f92367358d5c20048a3d86296e22bd8117b8

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
