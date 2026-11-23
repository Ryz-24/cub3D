/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 12:04:13 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/23 12:08:36 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *p, char c)
{
	p->dir_x = 0;
	p->dir_y = 0;
	if (c == 'E')
		p->dir_x = 1;
	else if (c == 'W')
		p->dir_x = -1;
	else if (c == 'N')
		p->dir_y = 1;
	else if (c == 'S')
		p->dir_y = -1;
	p->plane_x = p->dir_x * FOV;
	p->dir_x = p->dir_y * FOV;
}
