#include "cub3d.h"

static int	is_map_line(char *line)
{
	line = skip_spaces(line);
	return (*line == '1' || *line == '0');
}

static int	is_id(char *line, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	return (is_space(line[len]));
}

static void	handle_element(t_game *game, char *line)
{
	t_config	*cfg;

	cfg = &game->config;
	line = skip_spaces(line);
	if (is_id(line, "NO"))
		parse_texture(game, &cfg->textures.no, line + 2);
	else if (is_id(line, "SO"))
		parse_texture(game, &cfg->textures.so, line + 2);
	else if (is_id(line, "WE"))
		parse_texture(game, &cfg->textures.we, line + 2);
	else if (is_id(line, "EA"))
		parse_texture(game, &cfg->textures.ea, line + 2);
	else if (is_id(line, "F"))
		parse_color(game, &cfg->floor, line + 1);
	else if (is_id(line, "C"))
		parse_color(game, &cfg->ceiling, line + 1);
	else
		error_exit(game, "Invalid line before the map");
}

static int	all_elements_found(t_config *cfg)
{
	if (!cfg->textures.no || !cfg->textures.so
		|| !cfg->textures.we || !cfg->textures.ea)
		return (0);
	if (cfg->floor.r == -1 || cfg->ceiling.r == -1)
		return (0);
	return (1);
}

// reads the 6 elements, returns the index of the first map line
int	parse_elements(t_game *game)
{
	int	i;

	game->config.floor.r = -1;
	game->config.ceiling.r = -1;
	i = 0;
	while (game->lines[i] && !is_map_line(game->lines[i]))
	{
		if (*skip_spaces(game->lines[i]) != '\0')
			handle_element(game, game->lines[i]);
		i++;
	}
	if (!all_elements_found(&game->config))
		error_exit(game, "Missing element: need NO, SO, WE, EA, F and C");
	return (i);
}
