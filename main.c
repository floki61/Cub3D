#include "cub3d.h"

int	NO_PATH(t_data *img, char	*identifier, char	*path)
{
	if(!strcmp(identifier, "NO"))
	{	
		img->n_path = path;
		img->path.NO = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.NO);
	}
	return (-1);
}
int	SO_PATH(t_data *img, char	*identifier, char	*path)
{
	if(!strcmp(identifier, "SO"))
	{	
		img->s_path = path;
		img->path.SO = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.SO);
	}
	return (-1);
}
int	WE_PATH(t_data *img, char	*identifier, char	*path)
{
	if(!strcmp(identifier, "WE"))
	{	
		img->w_path = path;
		img->path.WE = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.WE);
	}
	return (-1);
}
int	EA_PATH(t_data *img, char	*identifier, char	*path)
{
	if(!strcmp(identifier, "EA"))
	{	
		img->e_path = path;
		img->path.EA = open(path, O_RDONLY);
		img->path.index += 1;
		return (img->path.EA);
	}
	return (-1);
}

void	free_tab(char	**str)
{
	int	i;

	i = -1;
	while(str[++i])
		free(str[i]);
}

int	path_texture(t_data *img, char	*path)
{
	char	**str;
	int		ret;
	
	ret = 0;
	str = ft_split(path, ' ');
	if(str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if(img->path.index == 0)
			ret = NO_PATH(img, str[0], str[1]);
		else if(img->path.index == 1)
			ret = SO_PATH(img, str[0], str[1]);
		else if(img->path.index == 2)
			ret = WE_PATH(img, str[0], str[1]);
		else if(img->path.index == 3)
			ret = EA_PATH(img, str[0], str[1]);
		// free_tab(str);
		if (ret != -1)
			return (1);
	}
	printf("--------ERROR--------\n");
	return (0);
		
}

int	is_num(char	*str)
{
	int i;

	i = -1;
	while(str[++i])
		if(str[i] < '0' && str[i] > '9')
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
	if(color_tab[2] && !color_tab[3])
	{	
		while(color_tab[i])
		{
			if(is_num(color_tab[i]))
			{
				color = atoi(color_tab[i]);
				if (color >= 0 && color <= 255)
				{
					if(i == 0)
						img->color.RedFloor = color;
					else if(i == 1)
						img->color.GreenFloor = color;
					else if(i == 2)
						img->color.BlueFloor = color;
				}
				else
					break;
				i++;
			}
			else
				break;
		}
		if(i == 3)
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
	if(color_tab[2] && !color_tab[3])
	{	
		while(color_tab[i])
		{
			if(is_num(color_tab[i]))
			{
				color = atoi(color_tab[i]);
				if (color >= 0 && color <= 255)
				{
					if(i == 0)
						img->color.RedCeilling = color;
					else if(i == 1)
						img->color.GreenCeilling = color;
					else if(i == 2)
						img->color.BlueCeilling = color;
				}
				else
					break;
				i++;
			}
			else
				break;
		}
		if(i == 3)
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
	if(str[0] && str[1] && !str[2])
	{
		str[1][ft_strlen(str[1]) - 1] = '\0';
		if(img->color.index == 0 && !strcmp(str[0], "F"))
			ret = FLOOR_COLOR(img, str[1]);
		else if(img->color.index == 1 && !strcmp(str[0], "C"))
			ret = CEILLING_COLOR(img, str[1]);
		free_tab(str);
		if(ret == 3)
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
		if(img->path.index < 4)
		{	
			if(strcmp(instruction,"\n"))
				if(!path_texture(img, instruction))
					exit (0);
		}
		else if(img->color.index < 2)
		{
			if(strcmp(instruction,"\n"))
				if(!set_color(img,	instruction))
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

void	init_data(t_data	*img, char	*fd)
{
	img->rays = NULL;
	img->img = NULL;
	img->wall_textur = NULL;
	img->color_buff = NULL;
	img->walkdirection2 = 0;
	img->walkdirection = 0;
	img->mini_scall = 0;
	img->path.index = 0;
	img->color.index = 0;
	img->fd = open(fd, O_RDONLY);
	if (!(img->fd) || !img)
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	return ;
}

void	read_images(t_data	*data)
{
	int hight;
	int with;

	data->n_textur_buffer.img = mlx_xpm_file_to_image(data->mlx, data->n_path, &with, &hight);
	data->s_textur_buffer.img = mlx_xpm_file_to_image(data->mlx, data->s_path, &with, &hight);
	data->e_textur_buffer.img = mlx_xpm_file_to_image(data->mlx, data->e_path, &with, &hight);
	data->w_textur_buffer.img = mlx_xpm_file_to_image(data->mlx, data->w_path, &with, &hight);
	data->n_textur_buffer.addr = mlx_get_data_addr(data->n_textur_buffer.img, &data->n_textur_buffer.bits_per_pixel, &data->n_textur_buffer.line_length, &data->n_textur_buffer.endian);
	data->s_textur_buffer.addr = mlx_get_data_addr(data->s_textur_buffer.img, &data->s_textur_buffer.bits_per_pixel, &data->s_textur_buffer.line_length, &data->s_textur_buffer.endian);
	data->e_textur_buffer.addr = mlx_get_data_addr(data->e_textur_buffer.img, &data->e_textur_buffer.bits_per_pixel, &data->e_textur_buffer.line_length, &data->e_textur_buffer.endian);
	data->w_textur_buffer.addr = mlx_get_data_addr(data->w_textur_buffer.img, &data->w_textur_buffer.bits_per_pixel, &data->w_textur_buffer.line_length, &data->w_textur_buffer.endian);
	// printf("%p \")
}

int	main(int argc, char **argv)
{
	t_data	img;

	check_name(argc ,argv[1]);
	init_data(&img, argv[1]);
	read_map(&img);
	open_window(&img);
}

