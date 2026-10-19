#include "cub3d.h"

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}

/*
** 2  = KeyPress,      mask 1L<<0 (KeyPressMask)
** 17 = DestroyNotify, the red cross
*/
void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 17, 0, close_window, game);
}
