/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmarad <malmarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:14:12 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 14:48:23 by malmarad         ###   ########.fr       */
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
	parse_file(&game, argv[1]);
	init_mlx(&game);
	init_img(&game);
	load_textures(&game);
	game.image.floor_color = pack_color(game.config.floor);
	game.image.ceil_color = pack_color(game.config.ceiling);
	cast_rays(&game);
	init_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
