# include "includes/cube3d.h"

void		ft_init_ray(t_engine *en, int x)
{
	en->ray.camera = 2 * x / (double)(en->width) - 1;
	en->ray.rposx = en->player_x;
	en->ray.rposy = en->player_y;
	en->ray.rdirx = en->ray.dirx + en->ray.planex * en->ray.camera;
	en->ray.rdiry = en->ray.diry + en->ray.planey * en->ray.camera;
	en->ray.rmapx = (int)en->ray.rposx;
	en->ray.rmapy = (int)en->ray.rposy;
	en->ray.rdisdx = fabs(1 / en->ray.rdirx);
	en->ray.rdisdy = fabs(1 / en->ray.rdiry);
}

void		ft_direction_ray(t_engine *en)
{
	if (en->ray.rdirx > 0)
	{
		en->ray.stepx = -1;
		en->ray.rdistx = (en->ray.rposx - en->ray.rmapx) * en->ray.rdisdx;
	}
	else
	{
		en->ray.stepx = 1;
		en->ray.rdistx = (en->ray.rmapx + 1.0 - en->ray.rposx) *
			en->ray.rdisdx;
	}
	if (en->ray.rdiry > 0)
	{
		en->ray.stepy = -1;
		en->ray.rdisty = (en->ray.rposy - en->ray.rmapy) * en->ray.rdisdy;
	}
	else
	{
		en->ray.stepy = 1;
		en->ray.rdisty = (en->ray.rmapy + 1.0 - en->ray.rposy) *
			en->ray.rdisdy;
	}
}

char		ray_wall_direction(t_engine *en)
{
	char	wall_direction;

	if (en->ray.wall == 0)
	{
		if (en->ray.stepx > 0 && en->ray.rmapx > \
		(int)en->ray.rposx && en->ray.wall == 0)
			wall_direction = 'W';
		if (en->ray.stepx < 0 && en->ray.rmapx < (int)\
		en->ray.rposx && en->ray.wall == 0)
			wall_direction = 'E';
	}
	if (en->ray.wall == 1)
	{
		if (en->ray.stepy > 0 && en->ray.rmapy > (int)en->ray.\
		rposy && en->ray.wall == 1)
			wall_direction = 'S';
		if (en->ray.stepy < 0 && en->ray.rmapy < (int)en->ray.\
		rposy && en->ray.wall - 0)
			wall_direction = 'N';
	}
	return (wall_direction);
}

char		ft_hit_ray(t_engine *en, char wall_direction)
{
	while (en->ray.hit == 0)
	{
		if (en->ray.rdistx < en->ray.rdisty)
		{
			en->ray.rdistx += en->ray.rdisdx;
			en->ray.rmapx += en->ray.stepx;
			en->ray.wall = 0;
		}
		else
		{
			en->ray.rdisty += en->ray.rdisdy;
			en->ray.rmapy += en->ray.stepy;
			en->ray.wall = 1;
		}
		if (!ft_strchr("02SWEN", en->map[en->ray.rmapy]\
					[en->ray.rmapx]))
			en->ray.hit = 1;
		wall_direction = ray_wall_direction(en);
	}
	return (wall_direction);
}

void		ft_size_ray(t_engine *en)
{
	if (en->ray.wall == 0)
		en->ray.dist = fabs((en->ray.rmapx - en->ray.rposx
					+ (1 - en->ray.stepx) / 2) / en->ray.rdirx);
	if (en->ray.wall == 1)
		en->ray.dist = fabs((en->ray.rmapy - en->ray.rposy
					+ (1 - en->ray.stepy) / 2) / en->ray.rdiry);
	en->ray.rh = fabs((en->height / en->ray.dist));
	en->ray.rh -= en->height / 50;
	en->ray.wstart = (-1 * (en->ray.rh)) / 2 + en->height / 2;
	en->ray.wend = en->ray.rh / 2 + en->height / 2;
	en->ray.spstart = (-1 * fabs((en->height / en->ray.sprite_dist)))\
					/ 2 + en->height / 2;
	en->ray.spstart = (en->ray.spstart < 0) ? 0 : en->ray.spstart;
	en->ray.spend = (fabs((en->height / en->ray.sprite_dist))) / 2\
					+ en->height / 2;
	en->ray.spend = (en->ray.spend > en->height) ? en->height : \
					en->ray.spend;
	if (en->ray.wstart < 0)
		en->ray.wstart = 0;
	if (en->ray.wend >= en->height)
		en->ray.wend = en->height - 1;
}