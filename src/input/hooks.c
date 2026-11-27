#include "cub3d.h"

// turns the flag of a movement key on (1) or off (0)
static void	set_key(t_game *game, int keycode, int value)
{
	if (keycode == KEY_W)
		game->keys.w = value;
	else if (keycode == KEY_A)
		game->keys.a = value;
	else if (keycode == KEY_S)
		game->keys.s = value;
	else if (keycode == KEY_D)
		game->keys.d = value;
	else if (keycode == KEY_LEFT)
		game->keys.left = value;
	else if (keycode == KEY_RIGHT)
		game->keys.right = value;
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game, 0);
	set_key(game, keycode, 1);
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	set_key(game, keycode, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}

/*
** 2  = KeyPress,      mask 1L<<0 (KeyPressMask)
** 3  = KeyRelease,    mask 1L<<1 (KeyReleaseMask)
** 17 = DestroyNotify, the red cross
*/
void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx.mlx, render_frame, game);
}
