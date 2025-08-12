/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:25:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/12 18:45:25 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_split_free(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

static void	free_partial_config(t_config *cfg)
{
	if (!cfg)
		return ;
	free(cfg->north_texture);
	free(cfg->south_texture);
	free(cfg->west_texture);
	free(cfg->east_texture);
	free(cfg->door_texture);
	ft_split_free(cfg->map);
	free(cfg);
}

static int	init_textures_and_colors(t_config *cfg)
{
	cfg->north_texture = ft_strdup(NORTH_TEXTURE_PATH);
	cfg->south_texture = ft_strdup(SOUTH_TEXTURE_PATH);
	cfg->west_texture = ft_strdup(WEST_TEXTURE_PATH);
	cfg->east_texture = ft_strdup(EAST_TEXTURE_PATH);
	cfg->door_texture = ft_strdup(DOOR_TEXTURE_PATH);
	if (!cfg->north_texture || !cfg->south_texture
		|| !cfg->west_texture || !cfg->east_texture
		|| !cfg->door_texture)
		return (0);
	cfg->floor_color = FLOOR_COLOR;
	cfg->ceiling_color = CEILING_COLOR;
	return (1);
}

static int	init_map_and_player(t_config *cfg)
{
	cfg->map = ft_split(
			"1111111111\n"
			"1000000001\n"
			"1011111101\n"
			"1000ND0001\n"
			"1010111101\n"
			"1000000001\n"
			"1111111111", '\n');
	if (!cfg->map)
		return (0);
	cfg->player_x = PLAYER_START_X;
	cfg->player_y = PLAYER_START_Y;
	cfg->player_dir = PLAYER_START_DIR;
	return (1);
}

t_config	*mock_config(void)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	if (!init_textures_and_colors(cfg))
	{
		free_partial_config(cfg);
		return (NULL);
	}
	if (!init_map_and_player(cfg))
	{
		free_partial_config(cfg);
		return (NULL);
	}
	return (cfg);
}
