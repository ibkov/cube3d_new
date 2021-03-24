#include "includes/cube3d.h"

int			check_map_same_size(t_map *map)
{
	t_map	*tmp;
	int		size;

	tmp = map;
	size = (int)ft_strlen(tmp->line);
	while (tmp)
	{
		if ((int)ft_strlen(tmp->line) != size)
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int			check_non_square_map(t_map *tmp, t_map *previous, int i, int j)
{
	t_map *next;

	tmp = tmp->next;
	next = tmp->next;
	while (tmp->next)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] != '1' && tmp->line[i] != ' ' && i >=\
			(int)ft_strlen(previous->line))
				return (ERROR_MAP_NOT_CLOSED);
			if (next)
				if (tmp->line[i] != '1' && tmp->line[i] != ' ' && i >=\
				(int)ft_strlen(next->line))
					return (ERROR_MAP_NOT_CLOSED);
			i++;
		}
		previous = tmp;
		tmp = tmp->next;
		next = tmp->next;
		j++;
	}
	return (SUCCESS);
}

int			check_map_closed(t_map *map)
{
	t_map	*tmp;
	int		i;

	tmp = map;
	if (check_non_square_map(tmp, tmp, 0, 1) != SUCCESS)
		return (ERROR_MAP_NOT_CLOSED);
	i = 0;
	while (tmp->line[i])
	{
		if (tmp->line[i++] != '1')
			return (ERROR_MAP_NOT_CLOSED);
	}
	while (tmp->next)
	{
		if (tmp->line[0] != '1')
			return (ERROR_MAP_NOT_CLOSED);
		if (tmp->line[ft_strlen(tmp->line) - 1] != '1')
			return (ERROR_MAP_NOT_CLOSED);
		tmp = tmp->next;
	}
	i = 0;
	while (tmp->line[i])
		if (tmp->line[i++] != '1')
			return (ERROR_MAP_NOT_CLOSED);
	return (SUCCESS);
}

int			check_map(t_map *map, int count_pos, int i)
{
	t_map	*tmp;

	tmp = map;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (!ft_strchr("012NSWE", tmp->line[i]))
				return (error_str(ERROR_WRONG_CHAR));
			if (ft_strchr("NSWE", tmp->line[i]))
				count_pos++;
			if (count_pos > 1)
				return (error_str(ERROR_MAP_MANY_POSITIONS));
			i++;
		}
		tmp = tmp->next;
	}
	if (!count_pos)
		return (error_str(ERROR_MAP_NO_POSITIONS));
	if (check_map_closed(map) != SUCCESS)
		return (error_str(ERROR_MAP_NOT_CLOSED));
	return (SUCCESS);
}
