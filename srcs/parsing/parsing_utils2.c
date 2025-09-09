/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:57:55 by dvlachos          #+#    #+#             */
/*   Updated: 2025/09/08 14:58:36 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_number(const char *s)
{
	if (!s || !*s)
		return (false);
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
