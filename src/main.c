/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:14:12 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/23 11:59:11 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// zero everything, so clean_exit() knows what is not allocated yet
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		error_exit(&game, "Usage: ./cub3D <map.cub>");
	(void)argv;
	init_mlx(&game);
	init_img(&game);
	game.image.ceil_color = 0xFF0000;
	game.image.floor_color = 0xF0F000;
	// game.image.floor_color = pack_color(game.config.floor);
	// game.image.ceil_color = pack_color(game.config.ceiling);
	init_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
