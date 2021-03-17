#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <math.h>
# include <stdio.h> 
# include <unistd.h>
# include <fcntl.h>

# define MAX_SCREEN_H 1440
# define MAX_SCREEN_W 2560

typedef	enum				e_error
{
	ERROR,
	SUCCESS,
	ERROR_ARGUMENTS,
	ERROR_MAP,
}							t_error;

typedef struct				s_rgb
{
	int						r;
	int						g;
	int						b;
}							t_rgb;

typedef struct				s_map
{
	char					*line;
	struct s_map			*next;
}							t_map;

typedef struct				s_arg
{
	int						screen_w;
	int						screen_h;
	char					*no;
	char					*so;
	char					*we;
	char					*ea;
	char					*sprite;
	t_rgb					floor;
	t_rgb					ceil;
	t_map					*map;
}							t_arg;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data; 
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	p_gmr
{
	double 		posX;
	double 		posY;
	double		dirX;
	double      dirY;
	double		planeX;
	double		planeY;
	double		texWidht;
	double		texHeight;
	char 		**worldMap;

	
}				pos_gamer;


typedef struct				s_move
{
	int						up;
	int						down;
	int						left;
	int						right;
	int						step_right;
	int						step_left;
	int						collision;
}							t_move;


typedef	struct				s_tex
{
	void					*tex_ptr;
	int						*tex_data;
	int						bpp;
	int						size_line;
	int						endian;
	int						width;
	int						height;
	char					*type;
	int						sprite_x;
	int						sprite_y;
}							t_tex;

typedef	struct				s_sprite
{
	double					pos_x;
	double					pos_y;
	t_tex					*tex;
}							t_sprite;

typedef struct				s_sprite_data
{
	double					sp_dist;
	double					spcamx;
	double					spcamy;
	double					transx;
	double					transy;
	int						spritescreenx;
	int						sprite_height;
	int						drawstart_y;
	int						drawend_y;
	int						sprite_width;
	int						drawstart_x;
	int						drawend_x;
	int						stripe;
	int						sp_x;
	int						sp_y;
}							t_sprite_data;

typedef	struct				s_engine
{
	void					*mlx_ptr;
	void					*win_ptr;
	t_arg					arg;
	char					**map;
	int						map_height;
	int						map_width;
	double					player_x;
	double					player_y;
	char					orientation;
	int						height;
	int						width;
	unsigned int			floor;
	unsigned int			ceil;
	int						error;
	t_move					move;
	t_img					*img;
	t_tex					*tex_s;
	t_tex					*tex_n;
	t_tex					*tex_w;
	t_tex					*tex_e;
	t_tex					*tex_sprite;
	int						save_flag;
	int						sprite_width;
	int						sprite_count;
	t_sprite				*sprite_tab;
	t_sprite_data			sprite;

}							t_engine;



typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	pos_gamer	pos;
	t_arg		args;
}				t_mlx;


int press_key(int keycode, t_mlx *mlx);
int draw_ray_casting(t_mlx *mlx);
void parcer_map(char *file_name, pos_gamer *pos);
int draw_ray_casting(t_mlx *mlx);
void init_position(pos_gamer *pos);
int check_texture_arg(t_mlx *mlx, char *buffer);
int check_arguments(t_mlx *mlx, char *buffer);
int check_fc_arg(t_mlx *mlx, char *buffer);
char *cor_start_ch(char *buffer);
int map_to_list(t_mlx *mlx, char *buffer);
int		ft_lst_sz(t_map *lst);

#endif
