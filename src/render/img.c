/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmarad <malmarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:13:35 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 14:49:10 by malmarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img(t_game *game)
{
	t_image	*img;

	img = &game->image;
	img->img = mlx_new_image(game->mlx.mlx, WIN_W, WIN_H);
	if (!img->img)
		error_exit(game, "mlx init image failed");
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		error_exit(game, "mlx_get_data_addr failed");
	img->height = WIN_H;
	img->width = WIN_W;
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

void	drawing_time(t_game *game)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < WIN_H)
	{
		if (i < WIN_H / 2)
			color = game->image.ceil_color;
		else
			color = game->image.floor_color;
		j = 0;
		while (j < WIN_W)
		{
			put_pixel(&game->image, j, i, color);
			j++;
		}
		i++;
	}
}

int	render_frame(t_game *game)
{
	drawing_time(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->image.img, 0, 0);
	return (0);
}
