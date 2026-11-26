/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 12:18:03 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 12:42:58 by maradweh         ###   ########.fr       */
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

/* -ROT -> LIFT
	ROT -> RIGHT	
*/
static	int	close_window(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}

/*
** 2  = KeyPress,      mask 1L<<0 (KeyPressMask)
** 17 = DestroyNotify, the red cross
*/
void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx.mlx, render_frame, game);
}
