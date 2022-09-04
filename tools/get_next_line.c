/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:29:17 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/03 17:00:02 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_before_line(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (ft_substr(str, 0, i + 1));
}

static char	*ft_after_line(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			s = ft_substr(str, i + 1, ft_strlen(str));
			free (str);
			return (s);
		}
		i++;
	}
	free (str);
	return (NULL);
}

static char	*ft_read_line(char	*str, int fd)
{
	char		*buff;
	int			i;

	i = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
	{
		free (buff);
		return (NULL);
	}
	while (ft_check_line(str) == 0 && i != 0)
	{
		i = read (fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[i] = '\0';
		str = ft_strjoin(str, buff);
	}
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_line(str, fd);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	s = ft_before_line(str);
	str = ft_after_line(str);
	return (s);
}
