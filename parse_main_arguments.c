# include "includes/cube3d.h"

int check_screen_arg(t_arg *arg, char *buffer)
{
  int i;
  
  i = 0;
  while(!ft_isdigit(buffer[i]) && !ft_strchr("+-" , buffer[i]))
      i++;
  arg->screen_w = ft_atoi(&buffer[i]);
  while(ft_isdigit(buffer[i]) || ft_strchr("+-" , buffer[i]))
      i++;
  arg->screen_h = ft_atoi(&buffer[i]);
  while ((ft_strchr("\t\v\r\f", buffer[i]) || ft_isdigit(buffer[i]))\
			&& buffer[i] != '\0')
		i++;
  if (arg->screen_h <= 0 || arg->screen_w <= 0)
		return (0);
  if (arg->screen_h >= MAX_SCREEN_H)
    arg->screen_h = MAX_SCREEN_H;
  if  (arg->screen_w >= MAX_SCREEN_W)
    arg->screen_w = MAX_SCREEN_W;
  return (SUCCESS);
}

int check_arguments(t_arg *arg, char *buffer)
{
    if (buffer[0] == '\0' || buffer[0] ==  '\n')
      return (SUCCESS);
    if (buffer[0] == 'R')
      if (check_screen_arg(arg, buffer) != SUCCESS)
        return (ERROR); 
    if (ft_strchr("NSWE", buffer[0]))
      if (check_texture_arg(arg, buffer) != SUCCESS)
        return (ERROR);  
    if (ft_strchr("FC", buffer[0]))
      if (check_fc_arg(arg, buffer) != SUCCESS)
        return (ERROR);
    if (ft_strchr(buffer, '1') && !ft_strchr("RNSEWFC", buffer[0]))
      if (map_to_list(arg, buffer) != SUCCESS)
        return (ERROR);
    if (!ft_isdigit(buffer[0]) && !ft_strchr("RNSEWFC ", buffer[0]))
      return (ERROR);
    return (SUCCESS);
}