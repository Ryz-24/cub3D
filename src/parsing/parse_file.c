#include "cub3d.h"

// the name must end in exactly ".cub" and have something before it
static int	check_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 5) != 0)
		return (0);
	return (1);
}

// get_next_line keeps the '\n', we don't want it in our lines
static void	remove_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

// makes the lines array one bigger and puts the new line at the end
static int	add_line(t_game *game, char *line, int count)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (0);
	i = 0;
	while (i < count)
	{
		new[i] = game->lines[i];
		i++;
	}
	new[count] = line;
	new[count + 1] = NULL;
	free(game->lines);
	game->lines = new;
	return (1);
}

static void	read_lines(t_game *game, int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (!add_line(game, line, count))
		{
			free(line);
			close(fd);
			error_exit(game, "Memory allocation failed");
		}
		count++;
		line = get_next_line(fd);
	}
}

void	parse_file(t_game *game, char *path)
{
	int	fd;

	if (!check_extension(path))
		error_exit(game, "Map file must have a .cub extension");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(game, "Cannot open map file");
	read_lines(game, fd);
	close(fd);
	if (!game->lines)
		error_exit(game, "Map file is empty");
	parse_map(game, parse_elements(game));
	free_grid(game->lines);
	game->lines = NULL;
}
