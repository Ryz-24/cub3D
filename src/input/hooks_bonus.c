/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmarad <malmarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 14:41:25 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 15:08:49 by malmarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(int keycode, t_game *game)
{
	t_player	*p;

	p = &game->player;
	if (keycode == KEY_W)
		move_player(game, p->dir_x * MOVE_SPEED, p->dir_y * MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(game, -p->dir_x * MOVE_SPEED, -p->dir_y * MOVE_SPEED);
	else if (keycode == KEY_A)
		move_player(game, p->dir_y * MOVE_SPEED, -p->dir_x * MOVE_SPEED);
	else if (keycode == KEY_D)
		move_player(game, -p->dir_y * MOVE_SPEED, p->dir_x * MOVE_SPEED);
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game, 0);
	else if (keycode == KEY_LEFT)
		rotate_player(&game->player, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(&game->player, ROT_SPEED);
	else
		handle_movement(keycode, game);
	return (0);
}

static int	close_window(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}

static int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			delta_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	last_x = x;
	rotate_player(&game->player, delta_x * 0.003);
	return (0);
}

void	init_bonus_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 17, 0, close_window, game);
	mlx_hook(game->mlx.win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx.mlx, render_frame, game);
}
