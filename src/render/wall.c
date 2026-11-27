#include "cub3d.h"

/*
** Find the perpendicular distance from the player to the wall.
** DDA already increased side_x or side_y after the wall step,
** so subtract one delta to get the distance to the hit boundary.
*/
static void	set_wall_distance(t_ray *r)
{
	if (r->side == 0)
		r->perp_dist = r->side_x - r->delta_x;
	else
		r->perp_dist = r->side_y - r->delta_y;
}

/*
** Texture array:
** 0 = north, 1 = south, 2 = west, 3 = east.
*/
static t_wall_texture	*select_texture(t_game *g)
{
	if (g->ray.side == 0)
	{
		if (g->ray.dir_x > 0)
			return (&g->wall_textures[3]);
		return (&g->wall_textures[2]);
	}
	if (g->ray.dir_y > 0)
		return (&g->wall_textures[1]);
	return (&g->wall_textures[0]);
}

/*
** Find the column of the texture corresponding to the
** position where the ray hit the wall.
*/
static int	get_texture_x(t_game *g, t_wall_texture *tex)
{
	double	hit;
	int		tex_x;

	if (g->ray.side == 0)
		hit = g->player.y + g->ray.perp_dist * g->ray.dir_y;
	else
		hit = g->player.x + g->ray.perp_dist * g->ray.dir_x;
	hit -= floor(hit);
	tex_x = (int)(hit * tex->width);
	if ((g->ray.side == 0 && g->ray.dir_x < 0)
		|| (g->ray.side == 1 && g->ray.dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

/*
** Draw one textured wall stripe at screen column x.
*/
static void	tex_loop(t_game *g, t_wall_draw *wall, int x, int y)
{
	int		tex_y;
	char	*pixel;

	while (y < wall->end)
	{
		tex_y = (int)((y - wall->top) / wall->height
				* wall->tex->height);
		if (tex_y >= wall->tex->height)
			tex_y = wall->tex->height - 1;
		pixel = wall->tex->addr + tex_y * wall->tex->line_len
			+ wall->tex_x * (wall->tex->bpp / 8);
		put_pixel(&g->image, x, y, *(unsigned int *)pixel);
		y++;
	}
}

void	draw_wall(t_game *g, int x)
{
	t_wall_draw	wall;
	int			y;

	set_wall_distance(&g->ray);
	if (g->ray.perp_dist <= 0)
		return ;
	wall.tex = select_texture(g);
	if (wall.tex->bpp != 32)
		error_exit(g, "Expected a 32-bit wall texture");
	wall.tex_x = get_texture_x(g, wall.tex);
	wall.height = WIN_H / g->ray.perp_dist;
	wall.top = (WIN_H - wall.height) / 2.0;
	y = 0;
	if (wall.top > 0)
		y = (int)ceil(wall.top);
	wall.end = WIN_H;
	if (wall.top + wall.height < WIN_H)
		wall.end = (int)ceil(wall.top + wall.height);
	tex_loop(g, &wall, x, y);
}