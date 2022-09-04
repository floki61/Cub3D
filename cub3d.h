#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>

typedef struct s_node
{
	int		c;
	int		e;
	int		p;
	int		x;
	int		y;
	int		lenght;
	int		width;
	void	*player1;
	void	*player2;
	void	*player3;
	void	*player4;
	void	*exit;
	void	*exit2;
	void	*ground;
	void	*block;
	void	*envr;
	void	*lava;
}				t_node;

typedef struct s_player
{
	int	x;
	int y;
}	t_player;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*relative_path;
	char	**map;
	int		img_width;
	int		img_height;
	int		px;
	int		py;
	int		c;
	int		indx;
	int		fd;
	int		p_p;
	t_node	var;
	t_player	player;
}				t_data;


char	*get_next_line(int fd);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
void	ft_putstr(char *s);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		check_map(char **map, t_node *var, t_data *img);
int		check_lenght(char **map, int i, t_node *var);
int		check_width(char **map, int i);
int		check_middle(char **map, t_node *var, t_data *img);
int		open_window(t_data *img, t_node *var);
void	so_long(t_data *img, t_node *var);
void	drawing(char map, t_data	*img);
void	search_map(t_data *img, char n);
void	draw(t_data *img);
void	moves1(int keycode, t_data *img);
void	moves2(int keycode, t_data *img);
void	moves3(t_data *img, int py, int px);
int		key_hook(int keycode, t_data *img);
int		destroy(t_data *data);
void	put_player(t_data *img);
int		check_name(int	argc, char *str);
void	put_string(t_data *img);
void	find_player(t_player *player, t_data *img);

#endif
