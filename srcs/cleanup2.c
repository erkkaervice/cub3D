/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:48:49 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/26 13:48:50 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_cfg_textures_paths(t_config *cfg)
{
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
	if (cfg->sprite_texture)
		free(cfg->sprite_texture);
	cfg->ceiling_color = NULL;
	cfg->floor_color = NULL;
	cfg->north_texture = NULL;
	cfg->south_texture = NULL;
	cfg->west_texture = NULL;
	cfg->east_texture = NULL;
	cfg->door_texture = NULL;
	cfg->sprite_texture = NULL;
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
