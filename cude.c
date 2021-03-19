
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

int check_main_arg(int argc, char **argv)
{
  if (argc > 3)
    return (ERROR);
  if(argc < 2)
    return (ERROR);
  if (argc == 2)
    if (!(ft_strncmp(argv[1] + ft_strlen(argv[1] - 4) , ".cub", 4)))
      return (ERROR);
  if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6))
			return (ERROR);
  return (SUCCESS);
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
		ft_disp_col(env, x++, tex, 0);
		env->ray.zbuffer[x] = env->ray.dist;
	}
  return (1);
}

int ft_redraw(t_engine *en)
{
  free_img(en, en->img);
  en->img = ft_new_image(en, en->args.screen_w, en->args.screen_h);
  ft_disp_screen(en, 0);
  mlx_put_image_to_window(en->mlx_ptr, en->win_ptr, en->img->img_ptr, 0, 0);

  return (SUCCESS);
}


void run_game(t_engine en)
{
    // init_position(&en.pos);
    en.mlx_ptr = mlx_init();
    en.win_ptr = mlx_new_window(en.mlx_ptr, en.args.screen_w, en.args.screen_h, "Game cube3d school_21");
    // draw_ray_casting(&mlx);
    mlx_hook(en.win_ptr, 2, 1L<<0, press_key, &en);
    // mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    mlx_loop_hook(en.mlx_ptr, ft_redraw, &en);
    mlx_loop(en.mlx_ptr);
}

int check_map_run(int argc, char **argv, t_mlx *mlx)
{

  t_engine en;
  printf("%s", argv[1]);
  argc = 0;
  ft_bzero(&en, sizeof(t_engine));
  ft_bzero(&en.ray, sizeof(t_ray));
  en.map = map_to_matrix(mlx->args.map);
  run_game(en);
  return (SUCCESS);
}



int main(int argc, char **argv)
{
  t_mlx	mlx;
  int fd;
  char *buffer;
  int check_file;

  check_file = 0;
  ft_bzero(&mlx.args, sizeof(mlx.args));
  fd = open(argv[1], O_RDWR);
  if (check_main_arg(argc, argv) != SUCCESS)
		return (0);
  while ((check_file = get_next_line(fd, &buffer)) > 0)
	{
      if (check_arguments(&mlx, buffer) != SUCCESS)
        return (ERROR_ARGUMENTS);
      free(buffer);
  }
  if (check_arguments(&mlx, buffer) != SUCCESS)
      return (ERROR_ARGUMENTS);
  // ft_lstwrite(mlx.args.map);
  if (buffer)
    free(buffer);
  if (check_map_run(argc, argv, &mlx) != SUCCESS)
	  return (ERROR_MAP);
  return (SUCCESS);
}