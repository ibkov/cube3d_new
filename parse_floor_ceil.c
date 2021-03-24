# include "includes/cube3d.h"

int fc_color_r(t_arg *arg, char *buffer, int *i)
{
  int nbr;

  while (!ft_isdigit(buffer[*i]) && buffer[*i] != '-')
	  *i = *i + 1;
  if (ft_atoi(&buffer[*i]) > 255 || ft_atoi(&buffer[*i]) < 0)
		return (ERROR);
  nbr = ft_atoi(&buffer[*i]);
  if (buffer[0] == 'F')
    arg->floor.r = nbr;
  else
    arg->ceil.r = nbr;
  *i += ft_nbr_len(nbr, 10);
  return (SUCCESS);
}

int fc_color_g(t_arg *arg, char *buffer, int *i)
{
  int nbr;

  while (!ft_isdigit(buffer[*i]) && buffer[*i] != '-')
	  *i = *i + 1;
  if (ft_atoi(&buffer[*i]) > 255 || ft_atoi(&buffer[*i]) < 0)
		return (ERROR);
  nbr = ft_atoi(&buffer[*i]);
  if (buffer[0] == 'F')
    arg->floor.g = nbr;
  else
    arg->ceil.g = nbr;
  *i += ft_nbr_len(nbr, 10);
  return (SUCCESS);
}

int fc_color_b(t_arg *arg, char *buffer, int *i)
{
  int nbr;

  while (!ft_isdigit(buffer[*i]) && buffer[*i] != '-')
	  *i = *i + 1;
  if (ft_atoi(&buffer[*i]) > 255 || ft_atoi(&buffer[*i]) < 0)
		return (ERROR);
  nbr = ft_atoi(&buffer[*i]);
  if (buffer[0] == 'F')
    arg->floor.b = nbr;
  else
    arg->ceil.b = nbr;
  *i += ft_nbr_len(nbr, 10);
  return (SUCCESS);
}


int check_fc_arg(t_arg *arg, char *buffer)
{
  int i;

  i = 0;
  if (fc_color_r(arg, buffer, &i) != SUCCESS)
	  return (ERROR);
  if (fc_color_g(arg, buffer, &i) != SUCCESS)
	  return (ERROR);
  if (fc_color_b(arg, buffer, &i) != SUCCESS)
	  return (ERROR);
  return (SUCCESS);
}