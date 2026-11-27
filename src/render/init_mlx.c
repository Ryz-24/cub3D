#include "cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit(game, "mlx_init failed");
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIN_W, WIN_H, "cub3D");
	if (!game->mlx.win)
		error_exit(game, "mlx_new_window failed");
}
