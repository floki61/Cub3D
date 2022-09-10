/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:32:45 by oel-berh          #+#    #+#             */
/*   Updated: 2022/09/10 05:48:37 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	p = NULL;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	p = malloc((i + 1) * sizeof(char));
	if (!(p))
		return (NULL);
	while (i > 0)
	{
		p[j] = src[j];
		j++;
		i--;
	}
	p[j] = '\0';
	return (p);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		str1;
	int		str2 = 0;
	int		strr1;

	i = -1;
	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2);
	ret = (char *) malloc(sizeof(char) * (str1 + str2 + 1));
	if (!ret)
	{
		free (ret);
		return (NULL);
	}
	if (s1)
		while (s1[++i])
			ret[i] = s1[i];
	strr1 = str1;
	i = 0;
	while (s2[i])
		ret[str1++] = s2[i++];
	ret[strr1 + str2] = '\0';
	free(s1);
	return (ret);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*c;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0' || start > ft_strlen(s))
	{
		c = malloc(1 * sizeof(char));
		if (!c)
			return (NULL);
		c[0] = '\0';
		return (c);
	}
	c = (char *)malloc((len + 1) * sizeof(char));
	if (!c)
		return (NULL);
	while (s[start] && len > 0)
	{
		c[j++] = s[start++];
		len--;
	}
	c[j] = '\0';
	return (c);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write (1, &s[i++], 1);
	write(1, "\n", 1);
}

void	search_map(t_data *img, char n)
{
	int	i;
	int	j;

	i = 0;
	while (img->map[i])
	{
		j = 0;
		while (img->map[i][j])
		{
			if (img->map[i][j] == n)
			{
				img->px = j;
				img->py = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

