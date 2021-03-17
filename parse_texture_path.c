#include "includes/cube3d.h"


int texture_add(t_mlx *mlx, char *buffer, char *texture_side, int i)
{
  if (!ft_strncmp("NO", texture_side, 2))
    if (!(mlx->args.no = ft_strdup(&buffer[i])))
      return (ERROR);
  if (!ft_strncmp("SO", texture_side, 2))
    if (!(mlx->args.so = ft_strdup(&buffer[i])))
      return (ERROR);
  if (!ft_strncmp("WE", texture_side, 2))
    if (!(mlx->args.we = ft_strdup(&buffer[i])))
      return (ERROR);
  if (!ft_strncmp("EA", texture_side, 2))
    if (!(mlx->args.ea = ft_strdup(&buffer[i])))
      return (ERROR);
  if (!ft_strncmp("S ", texture_side, 2))
    if (!(mlx->args.sprite = ft_strdup(&buffer[i])))
      return (ERROR);
  return (SUCCESS);
}

int check_texture_arg(t_mlx *mlx, char *buffer)
{
  int i;
  char *texture_side;

  texture_side = NULL;
  i = 2;
  if (ft_strlen(buffer) < 1)
    return (ERROR);
  texture_side = (char*)malloc(sizeof(char) * i + 1);
  ft_strlcpy(texture_side, buffer, 3);
  while (ft_strchr(" \t\v\r\f", buffer[i]))
    i++;
  if (texture_add(mlx, buffer, texture_side, i) != SUCCESS)
    return (ERROR);
  return (SUCCESS);
}