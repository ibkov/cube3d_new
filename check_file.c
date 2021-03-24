# include "includes/cube3d.h"

int check_main_arg(int argc, char **argv)
{
  if (argc > 3)
    return (ERROR_MANY_ARGUMENTS);
  if(argc < 2)
    return (ERROR_FEW_ARGUMENTS);
  if (argc == 2)
    	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
        return (ERROR_EXTENSION);
  if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6))
			return (ERROR_FLAG_SAVE);
  return (SUCCESS);
}

int reading_file_gnl(int fd, char *buffer, t_arg *arg)
{
  while ((get_next_line(fd, &buffer)) > 0)
    {
        if (check_arguments(arg, buffer) != SUCCESS)
          return (ERROR_ARGUMENTS);
        free(buffer);
    }
    if (check_arguments(arg, buffer) != SUCCESS)
        return (ERROR_ARGUMENTS);
    return (SUCCESS);
}