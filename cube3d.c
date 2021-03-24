
# include "includes/cube3d.h"

void	ft_lstwrite(t_map *lst)
{
	if (!lst)
		return ;
	while (lst->next)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
  if (!lst->next)
		printf("%s\n", lst->line);
}

char		**map_to_matrix(t_map *lst)
{
	t_map	*temp;
	int		i;
	int		j;
	char	**matrix;

	temp = lst;
	if (!(matrix = malloc(sizeof(char*) * (ft_lst_sz(lst) + 1))))
		return (NULL);
	i = 0;
	while (i < ft_lst_sz(lst))
	{
		if (!(matrix[i] = malloc(sizeof(char) * (ft_strlen(temp->line) + 1))))
			return (NULL);
		j = 0;
		while (temp->line[j] != '\0')
		{
			matrix[i][j] = temp->line[j];
			j++;
		}
		matrix[i][j] = '\0';
		temp = temp->next;
		i++;
	}
	return (matrix);
}


t_img		*ft_new_image(t_engine *env, int width, int height)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if (!(img->img_ptr = mlx_new_image(env->mlx_ptr, width, height)))
		return (NULL);
	if (!(img->data = (int*)mlx_get_data_addr(img->img_ptr, &img->bpp,
		&img->size_l, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

void free_img(t_engine *en, t_img *img)
{
  if (img)
  {
    mlx_destroy_image(en->mlx_ptr, img->img_ptr);
    free(img);
    img = 0;
  }
}


int			ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y)
{
	if (p_y >= img->height || p_x >= img->width || p_x < 0\
	|| p_y < 0 || ((p_y * img->width + p_x) >= (img->width * img->height - 1)))
		return (ERROR);
	img->data[p_y * img->width + p_x] = color;
	return (SUCCESS);
}

char		*ft_disp_col(t_engine *env, int x, char tex, int y)
{
	char	*tex_path;
	int		height;

 	tex_path = NULL;
	if (tex == 'E')
		height = env->tex_e->height;
	if (tex == 'N')
		height = env->tex_n->height;
	if (tex == 'W')
		height = env->tex_w->height;
	if (tex == 'S')
		height = env->tex_s->height;
	while (y < env->ray.wstart)
		ft_put_pixel(env->img, env->ceil, x, y++);
	while (y >= env->ray.wstart && y <= env->ray.wend)
	{
		env->ray.tex_y = (int)env->ray.tex_pos & (height - 1);
		env->ray.tex_pos += env->ray.step_tex;
		ft_put_pixel(env->img, env->color, x, y);
		y++;
	}
	while (y < env->height)
		ft_put_pixel(env->img, env->floor, x, y++);
	return (tex_path);
}

int			init_raybuffer(t_engine *env)
{
	if (!(env->ray.zbuffer = malloc(sizeof(double) * (env->width + 1))))
		return (ERROR);
	return (SUCCESS);
}

int			ft_disp_screen(t_engine *env, int x)
{
	char tex;

	while (x < env->width)
	{
		ft_init_ray(env, x);
		ft_direction_ray(env);
		tex = ft_hit_ray(env, 0);
		ft_size_ray(env);
		ft_wall_tex(env, tex);
		ft_disp_col(env, x, tex, 0);
		env->ray.zbuffer[x] = env->ray.dist;
    	x++;
	}
  return (1);
}

int ft_redraw(t_engine *en)
{
  free_img(en, en->img);
  en->img = ft_new_image(en, en->width, en->height);
  ft_disp_screen(en, 0);
  mlx_put_image_to_window(en->mlx_ptr, en->win_ptr, en->img->img_ptr, 0, 0);

  return (SUCCESS);
}


void run_game(t_engine en)
{
    // init_position(&en.pos);
    en.mlx_ptr = mlx_init();
    en.win_ptr = mlx_new_window(en.mlx_ptr, en.width, en.height, "Game cube3d school_21");
    // draw_ray_casting(&mlx);
    // mlx_hook(en.win_ptr, 2, 1L<<0, press_key, &en);
    
    ft_redraw(&en);
    // mlx_put_image_to_window(en.mlx_ptr, en.win_ptr, en.img->img_ptr, 0, 0);
    // mlx_loop_hook(en.mlx_ptr, ft_redraw, &en);
    mlx_loop(en.mlx_ptr);
}

void		get_arg_for_env(t_engine *env, t_arg arg, int y, int x)
{
	t_map	*tmp;

	tmp = arg.map;
	while (tmp)
	{
		x = 0;
		while (tmp->line[x] != '\0')
		{
			if (ft_strchr("NSWE", tmp->line[x]))
			{
				env->orientation = tmp->line[x];
				env->player_x = x++;
				env->player_y = y++;
			}
			if (ft_strchr("2", tmp->line[x]))
				env->sprite_count++;
			x++;
		}
		env->map_width = x;
		tmp = tmp->next;
		y++;
	}
	env->map_height = y - 1;
}

void		init_env_orientation(t_engine *env)
{
	if (env->orientation == 'N')
	{
		env->ray.diry = -0.99;
		env->ray.planex = -0.80;
	}
	if (env->orientation == 'S')
	{
		env->ray.diry = 0.99;
		env->ray.planex = 0.80;
	}
	if (env->orientation == 'E')
	{
		env->ray.dirx = 0.99;
		env->ray.planey = -0.80;
	}
	if (env->orientation == 'W')
	{
		env->ray.dirx = -0.99;
		env->ray.planey = 0.80;
	}
}

int			from_rgb_to_hex(t_rgb color)
{
	int		output;

	output = 256 * 256 * color.r + 256 * color.g + color.b;
	return (output);
}

void		init_env_2(t_engine *env, t_arg arg)
{
	env->width = arg.screen_w;
	env->height = arg.screen_h;
	env->floor = from_rgb_to_hex(arg.floor);
	env->ceil = from_rgb_to_hex(arg.ceil);
	env->arg = arg;
	init_env_orientation(env);
	env->mlx_ptr = mlx_init();
	env->player_x += 0.2;
	env->player_y += 0.2;
}

t_tex	*ft_new_tex(t_engine *env, char *file, char *type)
{
	t_tex *tex;

	if (!(tex = malloc(sizeof(t_tex))))
		return (NULL);
	if (!(tex->tex_ptr = mlx_xpm_file_to_image(env->mlx_ptr, file,
		&tex->width, &tex->height)))
	{
		free(tex);
		return (NULL);
	}
	if (!(tex->tex_data = (int *)mlx_get_data_addr(tex->tex_ptr, &tex->bpp,
		&tex->size_line, &tex->endian)))
	{
		free(tex->tex_ptr);
		free(tex);
		return (NULL);
	}
	tex->type = type;
	return (tex);
}

void	init_tex_wall_sprite(t_engine *env)
{
	if ((env->tex_n = ft_new_tex(env, env->arg.no, "NO")) == NULL)
		env->error = ERROR;
	if ((env->tex_s = ft_new_tex(env, env->arg.so, "SO")) == NULL)
		env->error = ERROR;
	if ((env->tex_w = ft_new_tex(env, env->arg.we, "WE")) == NULL)
		env->error = ERROR;
	if ((env->tex_e = ft_new_tex(env, env->arg.ea, "EA")) == NULL)
		env->error = ERROR;
	if ((env->tex_sprite = ft_new_tex(env, env->arg.sprite, "sprite")) == NULL)
		env->error = ERROR;
}

int		init_tex(t_engine *env)
{
	env->error = 0;
	init_tex_wall_sprite(env);
	if (env->error)
	{
		env->error = ERROR;
		return (ERROR_MAP_NOT_CLOSED);
	}
	return (SUCCESS);
}

int			ft_lstsize_map(t_map *lst)
{
	t_map	*tmp;
	int		i;

	i = 0;
	if (!lst)
		return (i);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}


t_engine		init_env(t_arg arg)
{
	t_engine	env;

	ft_bzero(&env, sizeof(t_engine));
	ft_bzero(&env.ray, sizeof(t_ray));
	get_arg_for_env(&env, arg, 0, 0);
	env.ray.speed = 0.1;
	if (!(env.map = map_to_matrix(arg.map)))
	{
		env.error = ERROR;
			return  (env);
	}
	init_env_2(&env, arg);
	init_env_orientation(&env);
	init_tex(&env);
  env.map_height = ft_lstsize_map(env.arg.map);
	if ((env.error = init_raybuffer(&env)) != SUCCESS)
	{
		return  (env);
	}
	return (env);
}

int check_map_run(t_arg *arg, int argc)
{
  t_engine en;
  argc = 0;

  if (check_map(arg->map, 0, 0) != SUCCESS)
		return (ERROR_MAP);
  en = init_env(*arg);
  run_game(en);
  return (SUCCESS);
}

int main(int argc, char **argv)
{
  t_arg	arg;
  int fd;
  char *buffer;
  int err_num;

  err_num = 0;
  buffer = 0;
  ft_bzero(&arg, sizeof(arg));
  if ((err_num = check_main_arg(argc, argv)) != SUCCESS)
		return (error_str(err_num));
  if ((fd = open(argv[1], O_RDWR)) < 0)
    return (error_str(ERROR_READING_FILE));
  if ((err_num = reading_file_gnl(fd, buffer, &arg)) != SUCCESS)
    return (error_str(err_num));
  if (buffer)
    free(buffer);
  if (check_map_run(&arg, argc) != SUCCESS)
	  return (error_str(ERROR_MAP));
  return (SUCCESS);
}