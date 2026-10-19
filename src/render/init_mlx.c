#include "cub3d.h"

/*
** TEMPORARY so the project builds and a window opens.
** Rule from the contract: on any failure, call error_exit().
*/
void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit(game, "mlx_init failed");
	game->mlx.win = mlx_new_window(game->mlx.mlx, 1280, 720, "cub3D");
	if (!game->mlx.win)
		error_exit(game, "mlx_new_window failed");
}
