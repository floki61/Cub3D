#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.14159265
# define TILE_SIZE  64
# define W_WITHE  2000
# define W_HIGHTE  800
# define FOV_ANGLE (60 * (PI / 180))
# define WALL_STRIP_WIDTH 1
# define TEXTUR_WIDTH 64
# define TEXTUR_HIGHT 64
# define MINIMAP_SCALE_FACTOR img->mini_scall

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>
#include <math.h>

typedef struct s_node
{
	// int		e;
	// int		p;
	int		x;
	int		y;
	int		lenght;
}				t_node;
typedef struct s_path
{
	int	NO;
	int	SO;
	int	WE;
	int	EA;
	int	index;
}				t_path;

typedef	struct s_color
{
	int	RedFloor;
	int	GreenFloor;
	int	BlueFloor;
	int	RedCeilling;
	int	GreenCeilling;
	int	BlueCeilling;
	int	index;
} t_color;
typedef struct s_ray
{
	int		redline;
	int		*lenght;
}				t_ray;
typedef struct s_player
{
	int	x;
	int y;
}	t_player;

typedef	struct s_raytools
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

typedef	struct s_textur
{
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	unsigned int 	*addr;
}	t_textur;


typedef	struct s_cast
{
	// int		wall_strip_width;
	double	rayangle_pro;
	// double	fov_angle;
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
	void	*mlx;
	void	*mlx_win;
	char	**map;
	int		px;
	int		py;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	int		num_rays;
	double	rayangle;
	int mapx;
	int mapy;
	int		minimap;
	int		turndirection; // -1 if left +1 if right
	int		walkdirection; // -1 if back +1 if front
	int		walkdirection2;
	double	rotationangle; // p / 2
	double	rotationspeed; // 2 * (p / 180 )
	int		movespeed;	// 2
	int		movestep; 	// walkdirection * movespeed
	//
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char 	*addr;
	unsigned int	*wall_textur;
	t_ray	ray;
	t_cast	*rays;
	void	*img;
	double		mini_scall;
	int		img_h;
	int		img_w;
	int		g_w;
	unsigned int	*color_buff;
	t_path	path;
	t_textur	n_textur_buffer;
	t_textur	s_textur_buffer;
	t_textur	w_textur_buffer;
	t_textur	e_textur_buffer;
	t_color	color;
	// int		c;
	int		fd;
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
int		check_name(int	argc, char *str);
void	put_string(t_data *img);
void	read_images(t_data	*data);
void	find_player(t_player *player, t_data *img);
void	put_myplayer2(t_data *img);
int		loop_game(t_data	*img);

#endif
