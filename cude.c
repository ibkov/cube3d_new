
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


void run_game(t_mlx mlx)
{
    init_position(&mlx.pos);
    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, mlx.args.screen_w, mlx.args.screen_h, "Game cube3d school_21");
    draw_ray_casting(&mlx);
    mlx_hook(mlx.win, 2, 1L<<0, press_key, &mlx);
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);
}

int check_map_run(int argc, char **argv, t_mlx *mlx)
{
  argc = 0;
  printf("%s", argv[0]);
  mlx->pos.worldMap = map_to_matrix(mlx->args.map);
  run_game(*mlx);
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