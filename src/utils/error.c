/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:13:58 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/22 23:13:59 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
