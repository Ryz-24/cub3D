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

/*
** Order matters: images and window need the display, so the display
** goes last. When we add the 4 texture images, destroy them here too
*/
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

/*
** Works at any stage because main() zeroes the whole t_game first:
** anything not allocated yet is NULL and is skipped (free(NULL) is safe).
*/
void	clean_exit(t_game *game, int status)
{
	destroy_mlx(&game->mlx, &game->image);
	free_grid(game->map.grid);
	free_textures(&game->config.textures);
	exit(status);
}
