#include "cub3d.h"

// runs every frame: move the player, then draw
// rendering: call render_frame(game) here, after update_player
static int	game_loop(t_game *game)
{
	update_player(game);
	return (0);
}

// zero everything, so clean_exit() knows what is not allocated yet
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		error_exit(&game, "Usage: ./cub3D <map.cub>");
	parse_file(&game, argv[1]);
	init_mlx(&game);
	init_hooks(&game);
	mlx_loop_hook(game.mlx.mlx, game_loop, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
