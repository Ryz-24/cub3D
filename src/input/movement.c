#include "cub3d.h"
#include <math.h>

// the player can only stand on '0' cells
static int	is_blocked(t_game *game, double x, double y)
{
	return (game->map.grid[(int)y][(int)x] != '0');
}

// pushes the check point WALL_MARGIN further in the direction we move
static double	margin(double step)
{
	if (step > 0)
		return (WALL_MARGIN);
	if (step < 0)
		return (-WALL_MARGIN);
	return (0);
}

// x and y are checked separately: blocked on one axis,
// the player still moves on the other one (slides along the wall)
static void	try_move(t_game *game, double dx, double dy)
{
	t_player	*p;

	p = &game->player;
	if (!is_blocked(game, p->x + dx + margin(dx), p->y))
		p->x += dx;
	if (!is_blocked(game, p->x, p->y + dy + margin(dy)))
		p->y += dy;
}

// rotates dir and plane by the same angle (positive = turn right)
static void	rotate(t_player *p, double angle)
{
	double	old_x;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	old_x = p->dir_x;
	p->dir_x = old_x * c - p->dir_y * s;
	p->dir_y = old_x * s + p->dir_y * c;
	old_x = p->plane_x;
	p->plane_x = old_x * c - p->plane_y * s;
	p->plane_y = old_x * s + p->plane_y * c;
}

// called once per frame: applies every key that is held down
// forward = dir, right = (-dir_y, dir_x)
void	update_player(t_game *game)
{
	t_player	*p;
	t_keys		*k;
	double		fwd;
	double		side;

	p = &game->player;
	k = &game->keys;
	fwd = (k->w - k->s) * MOVE_SPEED;
	side = (k->d - k->a) * MOVE_SPEED;
	if (fwd != 0 || side != 0)
		try_move(game, p->dir_x * fwd - p->dir_y * side,
			p->dir_y * fwd + p->dir_x * side);
	if (k->right != k->left)
		rotate(p, (k->right - k->left) * ROT_SPEED);
}
