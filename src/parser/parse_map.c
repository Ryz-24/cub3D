#include "cub3d.h"

// index of the last line that is not empty (anything after it is ignored)
static int	find_map_end(t_game *game, int start)
{
	int	end;
	int	i;

	end = start;
	i = start;
	while (game->lines[i])
	{
		if (*skip_spaces(game->lines[i]) != '\0')
			end = i;
		i++;
	}
	return (end);
}

// checks every character of one map row, counts the players
// returns the length of the row
static int	check_line(t_game *game, char *line, int *players)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]))
			error_exit(game, "Invalid character in map");
		if (ft_strchr("NSEW", line[i]))
			(*players)++;
		i++;
	}
	return (i);
}

static void	check_rows(t_game *game, int start, int end)
{
	int	players;
	int	width;
	int	len;
	int	i;

	players = 0;
	width = 0;
	i = start;
	while (i <= end)
	{
		if (*skip_spaces(game->lines[i]) == '\0')
			error_exit(game, "Empty line inside the map");
		len = check_line(game, game->lines[i], &players);
		if (len > width)
			width = len;
		i++;
	}
	if (players == 0)
		error_exit(game, "No player start position (N, S, E or W) in map");
	if (players > 1)
		error_exit(game, "More than one player start position in map");
	game->map.width = width;
	game->map.height = end - start + 1;
}

// copies the map rows into map.grid, padding each row with spaces to width
static void	build_grid(t_game *game, int start)
{
	int		y;
	size_t	len;

	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		error_exit(game, "Memory allocation failed");
	y = 0;
	while (y < game->map.height)
	{
		game->map.grid[y] = malloc(game->map.width + 1);
		if (!game->map.grid[y])
			error_exit(game, "Memory allocation failed");
		ft_memset(game->map.grid[y], ' ', game->map.width);
		len = ft_strlen(game->lines[start + y]);
		ft_memcpy(game->map.grid[y], game->lines[start + y], len);
		game->map.grid[y][game->map.width] = '\0';
		y++;
	}
}

// start is the index of the first map line, given by parse_elements
void	parse_map(t_game *game, int start)
{
	int	end;

	if (!game->lines[start])
		error_exit(game, "No map in file");
	end = find_map_end(game, start);
	check_rows(game, start, end);
	build_grid(game, start);
	check_map(game);
	init_player(game);
}
