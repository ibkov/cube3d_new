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
	ERROR_MAIN_ARGUMENTS,
	ERROR_MANY_ARGUMENTS,
	ERROR_FEW_ARGUMENTS,
	ERROR_EXTENSION,
	ERROR_FLAG_SAVE,
	ERROR_READING_FILE,
	ERROR_WRONG_CHAR,
	ERROR_MAP,
	ERROR_MAP_MANY_POSITIONS,
	ERROR_MAP_NO_POSITIONS,
	ERROR_MAP_NOT_CLOSED,

}							t_error;

typedef struct				s_rgb
{
	int						r;
	int						g;
	int						b;
}							t_rgb;

typedef struct	s_stk
{
	double			x;
	double			y;
	double			d;
}				t_stk;

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
	int			width;
	int			height;
}				t_img;

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

typedef struct				s_ray
{
	double					planex;
	double					planey;
	double					stepx;
	double					stepy;
	double					dirx;
	double					diry;
	int						tex_x;
	int						tex_y;
	double					rposx;
	double					rposy;
	double					rdirx;
	double					rdiry;
	double					rdisdx;
	double					rdisdy;
	double					rdistx;
	double					rdisty;
	int						rmapx;
	int						rmapy;
	int						wall;
	int						wstart;
	int						wend;
	double					camera;
	int						hit;
	double					rh;
	double					step_tex;
	double					tex_pos;
	double					dist;
	double					speed;
	double					*zbuffer;
	int						*sp_order;
	double					*sp_distance;
	int						sprite;
	int						sprite_x;
	int						sprite_y;
	double					sprite_dist;
	double					spstart;
	double					spend;
}							t_ray;

typedef	struct				s_engine
{
	void					*mlx_ptr;
	void					*win_ptr;
	t_arg					args;
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
	t_arg					arg;
	t_ray					ray;
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
	unsigned int			color;
	t_stk					*s;

}							t_engine;

int 		check_texture_arg(t_arg *arg, char *buffer);
int 		check_arguments(t_arg *arg, char *buffer);
int 		check_fc_arg(t_arg *arg, char *buffer);
char 		*cor_start_ch(char *buffer);
int			map_to_list(t_arg *arg, char *buffer);
int			ft_lst_sz(t_map *lst);
void		ft_size_ray(t_engine *en);
char		ft_hit_ray(t_engine *en, char wall_direction);
char		ray_wall_direction(t_engine *en);
void		ft_direction_ray(t_engine *en);
void		ft_wall_tex(t_engine *en, char tex);
void		ft_init_ray(t_engine *en, int x);
int 		error_str(int error);
int			check_map(t_map *map, int count_pos, int i);
int 		reading_file_gnl(int fd, char *buffer, t_arg *arg);
int 		check_main_arg(int argc, char **argv);

#endif
