#include "cub3d.h"

static void	load_one(t_game *game, t_wall_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx.mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		error_exit(game, "Failed to load wall texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		error_exit(game, "Failed to access texture pixels");
}

void	load_textures(t_game *game)
{
	load_one(game, &game->wall_textures[0], game->config.textures.no);
	load_one(game, &game->wall_textures[1], game->config.textures.so);
	load_one(game, &game->wall_textures[2], game->config.textures.we);
	load_one(game, &game->wall_textures[3], game->config.textures.ea);
}
