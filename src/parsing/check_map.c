/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 14:55:28 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/23 14:55:29 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// cells the player can stand on: floor or the start position
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

static	int	is_spawn(char c)
{
	return ((c == 'N') || (c == 'S')
		|| (c == 'E') || (c == 'W'));
}

static void	set_player(t_game *game, int x, int y)
{
	char	spawn;

	spawn = game->map.grid[y][x];
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	init_player(&game->player, spawn);
	game->map.grid[y][x] = '0';
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
			if (is_spawn(game->map.grid[y][x]))
				set_player(game, x, y);
			x++;
		}
		y++;
	}
}
