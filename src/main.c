#include "cub3d.h"

// zero everything, so clean_exit() knows what is not allocated yet
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		error_exit(&game, "Usage: ./cub3D <map.cub>");
	(void)argv;
	init_mlx(&game);
	init_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
