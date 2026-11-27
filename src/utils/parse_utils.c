#include "cub3d.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

// returns a pointer to the first character that is not a space or a tab
char	*skip_spaces(char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}
