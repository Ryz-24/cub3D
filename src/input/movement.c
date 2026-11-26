/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 12:18:42 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 12:50:41 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x >= game->map.width || map_y >= game->map.height)
		return (0);
	return (game->map.grid[map_y][map_x] == '0');
}

void	move_player(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (can_move(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	rotate_player(t_player *p, double angle)
{
	double	old_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	old_x = p->dir_x;
	p->dir_x = p->dir_x * cos_angle - p->dir_y * sin_angle;
	p->dir_y = old_x * sin_angle + p->dir_y * cos_angle;
	old_x = p->plane_x;
	p->plane_x = p->plane_x * cos_angle - p->plane_y * sin_angle;
	p->plane_y = old_x * sin_angle + p->plane_y * cos_angle;
}
