# include "includes/cube3d.h"

int fc_color_r(t_mlx *mlx, char *buffer, int *i)
{
  int nbr;

  while (!ft_isdigit(buffer[*i]) && buffer[*i] != '-')
	  *i = *i + 1;
  if (ft_atoi(&buffer[*i]) > 255 || ft_atoi(&buffer[*i]) < 0)
		return (ERROR);
  nbr = ft_atoi(&buffer[*i]);
  if (buffer[0] == 'F')
    mlx->args.floor.r = nbr;
  else
    mlx->args.ceil.r = nbr;
  *i += ft_nbr_len(nbr, 10);
  return (SUCCESS);
}

int fc_color_g(t_mlx *mlx, char *buffer, int *i)
{
  int nbr;

  while (!ft_isdigit(buffer[*i]) && buffer[*i] != '-')
	  *i = *i + 1;
  if (ft_atoi(&buffer[*i]) > 255 || ft_atoi(&buffer[*i]) < 0)
		return (ERROR);
  nbr = ft_atoi(&buffer[*i]);
  if (buffer[0] == 'F')
    mlx->args.floor.g = nbr;
  else
    mlx->args.ceil.g = nbr;
  *i += ft_nbr_len(nbr, 10);
  return (SUCCESS);
}

int fc_color_b(t_mlx *mlx, char *buffer, int *i)
{
  int nbr;

  while (!ft_isdigit(buffer[*i]) && buffer[*i] != '-')
	  *i = *i + 1;
  if (ft_atoi(&buffer[*i]) > 255 || ft_atoi(&buffer[*i]) < 0)
		return (ERROR);
  nbr = ft_atoi(&buffer[*i]);
  if (buffer[0] == 'F')
    mlx->args.floor.b = nbr;
  else
    mlx->args.ceil.b = nbr;
  *i += ft_nbr_len(nbr, 10);
  return (SUCCESS);
}


int check_fc_arg(t_mlx *mlx, char *buffer)
{
  int i;

  i = 0;
  if (fc_color_r(mlx, buffer, &i) != SUCCESS)
	  return (ERROR);
  if (fc_color_g(mlx, buffer, &i) != SUCCESS)
	  return (ERROR);
  if (fc_color_b(mlx, buffer, &i) != SUCCESS)
	  return (ERROR);
  return (SUCCESS);
}