/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmarad <malmarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 09:08:25 by maradweh          #+#    #+#             */
/*   Updated: 2026/11/26 14:48:33 by malmarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

// returns a pointer to the first character that is not a space or a tab
char	*skip_spaces(char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}
