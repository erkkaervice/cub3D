/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:48:49 by dvlachos          #+#    #+#             */
/*   Updated: 2025/09/02 20:00:00 by eala-lah         ###   ########.fr       */
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

static void	free_cfg_paths(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->ceiling_color)
		free(cfg->ceiling_color);
	if (cfg->floor_color)
		free(cfg->floor_color);
	if (cfg->north_texture)
		free(cfg->north_texture);
	if (cfg->south_texture)
		free(cfg->south_texture);
	if (cfg->west_texture)
		free(cfg->west_texture);
	if (cfg->east_texture)
		free(cfg->east_texture);
	if (cfg->door_texture)
		free(cfg->door_texture);
	if (cfg->sprite_texture_0)
		free(cfg->sprite_texture_0);
	if (cfg->sprite_texture_1)
		free(cfg->sprite_texture_1);
	if (cfg->sprite_texture_2)
		free(cfg->sprite_texture_2);
	cleanup_cfg_textures_paths(cfg);
}

void	free_partial_config(t_config **cfg_ptr)
{
	int			i;
	t_config	*cfg;

	if (!cfg_ptr || !*cfg_ptr)
		return ;
	cfg = *cfg_ptr;
	i = 0;
	if (cfg->map)
	{
		while (cfg->map[i])
			free(cfg->map[i++]);
		free(cfg->map);
		cfg->map = NULL;
	}
	free_cfg_paths(cfg);
	free(cfg);
	*cfg_ptr = NULL;
}
