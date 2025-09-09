/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:47:03 by dvlachos          #+#    #+#             */
/*   Updated: 2025/09/05 10:49:13 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_last_line(char	*last_line)
{
	int		i;

	i = 0;
	while (last_line[i])
	{
		if (last_line[i] == '0')
			return (print_err(NULL, "Map is not closed", -1));
		i++;
	}
	return (1);
}
