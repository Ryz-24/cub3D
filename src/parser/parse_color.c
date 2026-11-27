#include "cub3d.h"

// reads one number (0-255) with optional spaces around it
// leading zeros are fine since they don't make the value bigger
static char	*read_value(t_game *game, char *str, int *out)
{
	int	value;

	str = skip_spaces(str);
	if (!ft_isdigit(*str))
		error_exit(game, "Invalid color: expected R,G,B");
	value = 0;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		if (value > 255)
			error_exit(game, "Color value out of range (0-255)");
		str++;
	}
	*out = value;
	return (skip_spaces(str));
}

static char	*skip_comma(t_game *game, char *str)
{
	if (*str != ',')
		error_exit(game, "Invalid color: expected R,G,B");
	return (str + 1);
}

// value is everything after the identifier: " 220 , 100 , 0 "
void	parse_color(t_game *game, t_color *color, char *value)
{
	int	r;
	int	g;
	int	b;

	if (color->r != -1)
		error_exit(game, "Duplicate color identifier");
	value = read_value(game, value, &r);
	value = skip_comma(game, value);
	value = read_value(game, value, &g);
	value = skip_comma(game, value);
	value = read_value(game, value, &b);
	if (*value != '\0')
		error_exit(game, "Invalid color: expected R,G,B");
	color->r = r;
	color->g = g;
	color->b = b;
}
