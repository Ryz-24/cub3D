#include "cub3d_bonus.h"

static int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			delta_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	last_x = x;
	rotate_player(&game->player, delta_x * 0.003);
	return (0);
}

// same keys as the mandatory part (init_hooks), plus mouse rotation
void	init_bonus_hooks(t_game *game)
{
	init_hooks(game);
	mlx_hook(game->mlx.win, 6, 1L << 6, mouse_move, game);
}
