/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:38:37 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/04 23:01:12 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int skip_lastspaces(char    *line)
{
	int	n;

	n = ft_strlen(line) - 1;
	while (line[n] == ' ' || line[n] == '\t')
		n--;
	return (n);
}

int skip_spaces(char    *line)
{
	int i;

	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int	height(char **map, t_node *var)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][skip_spaces(map[i])] != '1' || map[i][skip_lastspaces(map[i])] != '1')
			return (-1);
		i++;
	}
	var->lenght = i;
	return (i);
}

int	width(char **map, int i) //-> firt line must be 11111111111111
{
	int	n;

	n = skip_spaces(map[i]);
	while (map[i][n])
	{	
		if (map[i][n] != '1' && map[i][n] != ' ' && map[i][n] != '\t')
			return (-1);
		n++;
	}
	return (n);
}

int	middle(char **map, t_node *var, t_data *img)
{
	int	i;
	int	n;

	i = 1;
	img->c = 0;
	var->e = 0;
	var->p = 0;
	while (map[++i])
	{
		n = skip_spaces(map[i]);
		while (map[i][n])
		{
			// if (map[i][n] == 'C')
			// 	img->c += 1;
			// else if (map[i][n] == 'E')
			// 	var->e += 1;
			if (map[i][n] == 'P')
			{
				map[i][n] = '0';
				img->px = (80 * n) + 35;
				img->py = (80 * i) + 35;
				printf("px: %d\n",img->px);
				printf("py: %d\n",img->py);
				var->p += 1;
			}
			else if(map[i][n] == '0')
			{
				if(map[i - 1][n] == ' ' || map[i + 1][n] == ' ' || map[i][n + 1] == ' ' || map[i][n - 1] == ' ')
					return(-1);	
				else if(map[i - 1][n] == '\0' || map[i + 1][n] == '\0' || map[i][n + 1] == '\0' || map[i][n - 1] == '\0')
					return(-1);	
			}
			else if (map [i][n] != '1' && map[i][n] != ' ' && map[i][n] != '\t')
				return (-1);
			n++;
		}
	}
	// if (img->c < 1 || var->e < 1 || var->p != 1)
	// 	return (-1);
	return (0);
}

int	check_map(char	**map, t_node	*var, t_data	*img)
{
	if ((height(map, var)) == -1)
	{
		printf("height error\n");
		return (0);
	}
	if ((width(map, 0)) == -1)
	{
		printf("width0 error\n");
		return (0);
	}
	if ((width(map, var->lenght - 1)) == -1)
	{
		printf("width1 error\n");
		return (0);
	}
	if ((middle(map, var, img)) == -1)
	{
		printf("middle error\n");
		return (0);
	}
	return (1);
}



int	check_name(int argc, char *str)
{
	int		i;
	int		j;
	char	*s;
	
	if(argc != 2)
		exit(0);
	i = ft_strlen(str) - 4;
	j = 0;
	s = ".ber";
	if (i < 0)
		return (1);
	while ((str[i] != '\0' || s[j] != '\0') && (str[j] == s[j]))
	{
		i++;
		j++;
	}
	if(str[i] - s[j] != 0)
	{
		ft_putstr("Error Invalid File");
		exit(0);
	}
	return (0);
}
