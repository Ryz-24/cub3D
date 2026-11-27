#include "cub3d.h"

// dir is where the player looks (y grows downward, so north is 0,-1)
// plane is dir turned 90 degrees to the right, scaled by FOV
static void	set_direction(t_player *player, char c)
{
	player->dir_x = 0;
	player->dir_y = 0;
	if (c == 'N')
		player->dir_y = -1;
	else if (c == 'S')
		player->dir_y = 1;
	else if (c == 'E')
		player->dir_x = 1;
	else if (c == 'W')
		player->dir_x = -1;
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}

// finds the N/S/E/W cell, puts the player in the middle of it,
// then turns the cell into normal floor
void	init_player(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				set_direction(&game->player, c);
				game->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
