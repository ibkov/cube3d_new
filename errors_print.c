# include "includes/cube3d.h"

int error_str(int error)
{
  if (error == ERROR_MANY_ARGUMENTS)
    ft_putstr_fd("\033[31m\nERROR\nYou give a lot of arguments.\n\n\033[0m", 1);
  else if (error == ERROR_FEW_ARGUMENTS)
    ft_putstr_fd("\033[31m\nERROR\nYou give a few arguments.\n\n\033[0m", 1);
  else if (error == ERROR_EXTENSION)
    ft_putstr_fd("\033[31m\nERROR\nYour file has not extension \".cub\"\n\n\033[0m", 1);
  else if (error == ERROR_FLAG_SAVE)
    ft_putstr_fd("\033[31m\nERROR\nYour flag has not correct format \"--save\"\n\n\033[0m", 1);
  else if (error == ERROR_READING_FILE)
    ft_putstr_fd("\033[31m\nERROR\nNo such file in directory\n\n\033[0m", 1);
  else if (error == ERROR_MAP)
    ft_putstr_fd("\033[33mCorrect you map.\n\n\033[0m", 1);
  else if (error == ERROR_MAP_MANY_POSITIONS)
    ft_putstr_fd("\033[31m\nERROR\nYour map has no one gamer position\n\n\033[0m", 1);
  else if (error == ERROR_MAP_NO_POSITIONS)
    ft_putstr_fd("\033[31m\nERROR\nYour map has no gamer position\n\n\033[0m", 1);
  else if (error == ERROR_MAP_NOT_CLOSED)
    ft_putstr_fd("\033[31m\nERROR\nYour map not closed\n\n\033[0m", 1);
  return (ERROR);
}