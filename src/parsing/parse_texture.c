#include "cub3d.h"

// the path must end in .xpm and the file must open
static void	check_texture_file(t_game *game, char *path)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 5) != 0)
		error_exit(game, "Texture must be a .xpm file");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(game, "Cannot open texture file");
	close(fd);
}

// value is everything after the identifier: "   ./north.xpm   "
void	parse_texture(t_game *game, char **dst, char *value)
{
	size_t	len;

	if (*dst)
		error_exit(game, "Duplicate texture identifier");
	value = skip_spaces(value);
	if (*value == '\0')
		error_exit(game, "Missing texture path");
	len = 0;
	while (value[len] && !is_space(value[len]))
		len++;
	if (*skip_spaces(value + len) != '\0')
		error_exit(game, "Unexpected text after texture path");
	*dst = ft_substr(value, 0, len);
	if (!*dst)
		error_exit(game, "Memory allocation failed");
	check_texture_file(game, *dst);
}
