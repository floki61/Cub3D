/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:45:32 by mait-aad          #+#    #+#             */
/*   Updated: 2022/10/08 01:10:01 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.14159265
# define W_WITHE  2000
# define W_HIGHTE  800
# define WALL_STRIP_WIDTH 1
# define TILE_SIZE	64
# define TEXTUR_WIDTH	64
# define TEXTUR_HIGHT	64

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

typedef struct s_node
{
	int		x;
	int		y;
	int		lenght;
}				t_node;

typedef struct s_path
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	index;
}				t_path;

typedef struct s_color
{
	int	redfloor;
	int	greenfloor;
	int	bluefloor;
	int	redceilling;
	int	greenceilling;
	int	blueceilling;
	int	index;
}		t_color;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_raytools
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	int		down;
	int		up;
	int		right;
	int		left;
}	t_rays;

typedef struct s_textur
{
	void			*img;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned int	*addr;
}	t_textur;

typedef struct s_cast
{
	double	rayangle_pro;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	int		is_hor;
	float	wallhitx;
	float	wallhity;
	float	h_wallhitx;
	float	h_wallhity;
	float	v_wallhitx;
	float	v_wallhity;
	float	horzhitdistance;
	float	verthitdistance;
	float	distance;
	int		redline;
	t_rays	rayfacing;
	char	dir;
}	t_cast;

typedef struct s_data
{
	void			*mlx;
	int				t_w;
	int				t_h;
	void			*mlx_win;
	char			**map;
	int				px;
	int				py;
	char			*n_path;
	char			*s_path;
	char			*e_path;
	char			*w_path;
	int				num_rays;
	double			rayangle;
	int				mapx;
	int				mapy;
	int				minimap;
	int				turndirection;
	int				walkdirection;
	int				walkdirection2;
	double			rotationangle;
	double			rotationspeed;
	int				movespeed;
	float			fov_angle;
	float			h_yintercept;
	float			h_xintercept;
	float			v_yintercept;
	float			v_xintercept;
	int				movestep;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*addr;
	int				textureoffsetx;
	int				textureoffsety;
	unsigned int	*wall_textur;
	t_cast			*rays;
	void			*img;
	double			mini_scall;
	int				img_h;
	int				img_w;
	int				g_w;
	unsigned int	*color_buff;
	t_path			path;
	t_textur		n_textur_buffer;
	t_textur		s_textur_buffer;
	t_textur		w_textur_buffer;
	t_textur		e_textur_buffer;
	t_color			color;
	int				fd;
	t_node			var;
	t_player		player;
}				t_data;

char	*get_next_line(int fd);
int		create_trgb(int t, int r, int g, int b);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
void	ft_putstr(char *s);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		check_map(char **map, t_data *img);
int		check_lenght(char **map, int i, t_node *var);
int		check_width(char **map, int i);
int		check_middle(char **map, t_node *var, t_data *img);
int		open_window(t_data *img);
void	so_long(t_data *img, t_node *var);
void	drawing(char map, t_data	*img);
void	search_map(t_data *img, char n);
void	draw(t_data *img);
void	moves1(int keycode, t_data *img);
void	moves2(int keycode, t_data *img);
int		key_hook(int keycode, t_data *img);
int		key_hook2(int keycode, t_data *img);
void	put_player(t_data *img);
int		check_name(int argc, char *str);
void	put_string(t_data *img);
void	read_images(t_data	*data);
void	find_player(t_player *player, t_data *img);
void	put_myplayer2(t_data *img);
int		loop_game(t_data	*img);
void	pint_sc_gr(t_data *data, int top, int y, int x);
int		x_ofset(t_data *data, int x);
void	draw_the_3d(t_data	*data, int addr_index, int texture_index, int x);
int		get_top(int hight);
int		get_bottem(int hight);
void	read_images(t_data	*d);
void	castallrays(t_data	*img);
void	init_rays(t_data	*img);
void	normalizeangle(t_data	*img);
void	raysfacing(t_data	*img, int i);
int		haswallat(t_data	*img,int	x, int y);
float   distancebetweenpoints(float x1, float y1, float x2, float y2);
void	read_map(t_data *img);
#endif
