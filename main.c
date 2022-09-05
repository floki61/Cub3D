#include "cub3d.h"

void	read_map(t_data *img, t_node *var)
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
	if (!check_map(img->map, var, img))
	{
		ft_putstr("Error Invalide Map\n");
		exit (0);
	}
	return ;
}


void	init_data(t_data	*img, t_node	*var, char	*fd)
{
	img->fd = open(fd, O_RDONLY);
	if (!(img->fd) || !img || !var)
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data	*img;
	t_node	*var;

	img = malloc(sizeof(t_data));
	var = malloc(sizeof(t_node));
	check_name(argc ,argv[1]);
	init_data(img, var, argv[1]);
	read_map(img, var);
	open_window(img, var);
}