#include "cub3d.h"

static void	dda_step(t_ray *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

void	run_dda(t_game *g)
{
	t_ray	*r;

	r = &g->ray;
	while (!r->hit)
	{
		dda_step(r);
		if (r->map_x < 0 || r->map_x >= g->map.width
			|| r->map_y < 0 || r->map_y >= g->map.height)
			error_exit(g, "Ray escaped the map");
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
		else if (g->map.grid[r->map_y][r->map_x] == ' ')
			error_exit(g, "Ray reached outside the map");
	}
}
