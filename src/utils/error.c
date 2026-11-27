#include "cub3d.h"

void	error_exit(t_game *game, char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	clean_exit(game, 1);
}
