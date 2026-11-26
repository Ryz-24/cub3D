/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmarad <malmarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 20:14:43 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 14:49:29 by malmarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *g, int x)
{
	t_ray		*r;
	t_player	*p;

	r = &g->ray;
	p = &g->player;
	r->camera_x = 2.0 * x / WIN_W - 1.0;
	r->dir_x = p->dir_x + p->plane_x * r->camera_x;
	r->dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	r->delta_x = 1e30;
	r->delta_y = 1e30;
	if (r->dir_x != 0)
		r->delta_x = fabs(1.0 / r->dir_x);
	if (r->dir_y != 0)
		r->delta_y = fabs(1.0 / r->dir_y);
	r->hit = 0;
}

static void	init_side_x(t_ray *r, t_player *p)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (p->x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - p->x) * r->delta_x;
	}
}

static void	init_side_y(t_ray *r, t_player *p)
{
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (p->y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - p->y) * r->delta_y;
	}
}

void	cast_rays(t_game *g)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(g, x);
		init_side_x(&g->ray, &g->player);
		init_side_y(&g->ray, &g->player);
		run_dda(g);
		draw_wall(g, x);
		x++;
	}
}
