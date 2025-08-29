/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:25:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/29 15:35:52 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*mock_config(char *filename)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	ft_bzero(cfg, sizeof(t_config));
	if (!map_parsing(cfg, filename))
	{
		free_partial_config(cfg);
		return (NULL);
	}
	cfg->door_texture = ft_strdup(DOOR_TEXTURE_PATH);
	cfg->sprite_texture_0 = ft_strdup(SPRITE_TEXTURE_0_PATH);
	cfg->sprite_texture_1 = ft_strdup(SPRITE_TEXTURE_1_PATH);
	cfg->sprite_texture_2 = ft_strdup(SPRITE_TEXTURE_2_PATH);
	return (cfg);
}
