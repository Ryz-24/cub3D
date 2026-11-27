#include "cub3d.h"

int	pack_color(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}
