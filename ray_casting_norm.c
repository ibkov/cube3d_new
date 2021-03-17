#include "cub3d.h"

int			ft_get_tex_height(t_engine *en, char tex)
{
	int		height;

	height = 64;
	if (tex == 'E')
		height = en->tex_e->height;
	if (tex == 'N')
		height = en->tex_n->height;
	if (tex == 'W')
		height = en->tex_w->height;
	if (tex == 'S')
		height = en->tex_s->height;
	return (height);
}

int			ft_get_tex_width(t_engine *en, char tex)
{
	int		width;

	width = 64;
	if (tex == 'E')
		width = en->tex_e->width;
	if (tex == 'N')
		width = en->tex_n->width;
	if (tex == 'W')
		width = en->tex_w->width;
	if (tex == 'S')
		width = en->tex_s->width;
	return (width);
}

void		ft_wall_tex(t_engine *en, char tex)
{
	double	wallx;
	int		height;
	int		width;

	width = ft_get_tex_width(en, tex);
	height = ft_get_tex_height(en, tex);
	if (en->ray.wall == 0)
		wallx = en->ray.rposy - en->ray.dist * en->ray.rdiry;
	else
		wallx = en->ray.rposx - en->ray.dist * en->ray.rdirx;
	wallx -= (int)wallx;
	en->ray.tex_x = (int)(wallx * width);
	if (en->ray.wall == 0)
		en->ray.tex_x = width + en->ray.tex_x;
	else if (en->ray.wall == 1)
		en->ray.tex_x = width + en->ray.tex_x - 1;
	en->ray.step_tex = 1 * width / en->ray.rh;
	en->ray.tex_pos = (en->ray.wstart - en->height / 2\
	+ en->ray.rh / 2) * en->ray.step_tex - 1;
}