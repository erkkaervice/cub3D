/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:48:49 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/28 17:12:18 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_game *game, int count)
{
	int	i;

	if (!game || !game->textures)
		return ;
	i = 0;
	while (i < count)
	{
		if (game->textures[i])
		{
			if (game->textures[i]->img)
				mlx_delete_texture(game->textures[i]->img);
			free(game->textures[i]);
			game->textures[i] = NULL;
		}
		i++;
	}
}

void	free_partial_config(t_config *cfg)
{
	int	i;

	i = 0;
	if (!cfg)
		return ;
	if (cfg->map && cfg->map[i])
	{
		while (cfg->map[i])
			free(cfg->map[i++]);
	}
	if (cfg->map)
	{
		free(cfg->map);
	}
	free_cfg_textures(cfg);
	free(cfg);
}
