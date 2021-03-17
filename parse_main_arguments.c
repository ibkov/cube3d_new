# include "includes/cube3d.h"

int check_screen_arg(t_mlx *mlx, char *buffer)
{
  int i;
  
  i = 0;
  while(!ft_isdigit(buffer[i]) && !ft_strchr("+-" , buffer[i]))
      i++;
  mlx->args.screen_w = ft_atoi(&buffer[i]);
  while(ft_isdigit(buffer[i]) || ft_strchr("+-" , buffer[i]))
      i++;
  mlx->args.screen_h = ft_atoi(&buffer[i]);
  while ((ft_strchr("\t\v\r\f", buffer[i]) || ft_isdigit(buffer[i]))\
			&& buffer[i] != '\0')
		i++;
  if (mlx->args.screen_h <= 0 || mlx->args.screen_w <= 0)
		return (0);
  if (mlx->args.screen_h >= MAX_SCREEN_H)
    mlx->args.screen_h = MAX_SCREEN_H;
  if  (mlx->args.screen_w >= MAX_SCREEN_W)
    mlx->args.screen_w = MAX_SCREEN_W;
  return (SUCCESS);
}

// char *cor_start_ch(char *buffer)
// {
//   int len;
//   int i;
//   char ch; 
//   int count_s;

//   i = 0;
//   count_s = 0;
//   len = ft_strlen(buffer);
//   while (buffer[count_s] == ' ')
//     count_s++;
//   ch = buffer[count_s];
//   while (i < count_s)
//   {
//     buffer[i] = ch;
//     i++;
//   }
//   return (buffer);
// }

// char *cor_sp(char *buffer)
// {
//   int i;
//   int j;
//   char ch_r;
//   char ch_l;

//   i = 0;
//   j = 0;
//   while(buffer[j])
//   {
//     if (!ft_strchr("NWES2 ", buffer[i]))
//       ch_l = buffer[i];
//     if (buffer[i] == ' ' && i >= j)
//     {
//       while(buffer[i] == ' ')
//         i++;
//       ch_r = buffer[i];
//     }
//     if (buffer[j] == ' ' && !ft_strchr("NWES2", ch_r))
//       buffer[j] = ch_r;
//     else if (buffer[j] == ' ' && ft_strchr("NWES2", ch_r))
//       buffer[j] = ch_l;
//     j++;
//     if (i < j)
//       i++;
//   }
//   return (buffer);
// }

int check_arguments(t_mlx *mlx, char *buffer)
{
    if (buffer[0] == '\0' || buffer[0] ==  '\n')
      return (SUCCESS);
    if (buffer[0] == 'R')
      if (check_screen_arg(mlx, buffer) != SUCCESS)
        return (ERROR); 
    if (ft_strchr("NSWE", buffer[0]))
      if (check_texture_arg(mlx, buffer) != SUCCESS)
        return (ERROR);  
    if (ft_strchr("FC", buffer[0]))
      if (check_fc_arg(mlx, buffer) != SUCCESS)
        return (ERROR);
    if (ft_strchr(buffer, '1') && !ft_strchr("RNSEWFC", buffer[0]))
      if (map_to_list(mlx, buffer) != SUCCESS)
        return (ERROR);
    if (!ft_isdigit(buffer[0]) && !ft_strchr("RNSEWFC ", buffer[0]))
      return (ERROR);
    return (SUCCESS);
}