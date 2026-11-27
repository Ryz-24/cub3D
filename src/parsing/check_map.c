#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// a walkable cell leaks if it is on the edge of the grid
// or if one of its 4 sides (up, down, left, right) is a space
static int	touches_outside(t_map *map, int x, int y)
{
	if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
		return (1);
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ')
		return (1);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

void	check_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_walkable(game->map.grid[y][x])
				&& touches_outside(&game->map, x, y))
				error_exit(game, "Map is not closed by walls");
			x++;
		}
		y++;
	}
}
