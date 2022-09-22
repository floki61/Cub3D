#include "cub3d.h"

void	read_map(t_data *img)
{
	char	*instruction;
	char	*tab;

	instruction = get_next_line(img->fd);
	if (!instruction)
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	tab = NULL;
	while (instruction)
	{
		tab = ft_strjoin(tab, instruction);
		free(instruction);
		instruction = get_next_line(img->fd);
	}
	img->map = ft_split(tab, '\n');
	if (!check_map(img->map, img))
	{
		ft_putstr("Error Invalide Map\n");
		exit (0);
	}
	return ;
}


void	init_data(t_data	*img, char	*fd)
{
	img->ray = malloc(sizeof(t_ray));
	img->rays = malloc(sizeof(t_cast));
	img->rayfacing = malloc(sizeof(t_rays));
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
	t_data	*img;

	img = malloc(sizeof(t_data));
	check_name(argc ,argv[1]);
	init_data(img, argv[1]);
	read_map(img);
	open_window(img);
}