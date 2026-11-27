#include "cub3d.h"

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	free_textures(t_texture *tex)
{
	free(tex->no);
	free(tex->so);
	free(tex->we);
	free(tex->ea);
}

static void	destroy_mlx(t_mlx *mlx, t_image *image)
{
	if (!mlx->mlx)
		return ;
	if (image->img)
		mlx_destroy_image(mlx->mlx, image->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

static void	destroy_wall_textures(t_game *game)
{
	int	i;

	if (!game->mlx.mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->wall_textures[i].img)
			mlx_destroy_image(game->mlx.mlx,
				game->wall_textures[i].img);
		i++;
	}
}

void	clean_exit(t_game *game, int status)
{
	destroy_wall_textures(game);
	destroy_mlx(&game->mlx, &game->image);
	free_grid(game->map.grid);
	free_grid(game->lines);
	free_textures(&game->config.textures);
	exit(status);
}
