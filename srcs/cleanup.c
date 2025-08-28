/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/28 17:16:10 by eala-lah         ###   ########.fr       */
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

static void	cleanup_map_and_textures(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->frame)
		mlx_delete_image(game->mlx, game->frame);
	if (game->z_buffer)
		free(game->z_buffer);
	if (game->textures)
	{
		i = 0;
		while (i < TEXTURE_COUNT)
		{
			if (game->textures[i])
			{
				if (game->textures[i]->img)
					mlx_delete_texture(game->textures[i]->img);
				free(game->textures[i]);
			}
			i++;
		}
	}
	cleanup_cfg_textures_paths(game->cfg);
}

static void	cleanup_sprites_and_doors(t_game *game)
{
	if (!game)
		return ;
	if (game->sprites)
	{
		free(game->sprites);
		game->sprites = NULL;
		game->num_sprites = 0;
	}
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
		game->num_doors = 0;
	}
}

static void	cleanup_cfg(t_game *game)
{
	int	i;

	if (!game || !game->cfg)
		return ;
	if (game->cfg->map)
	{
		i = 0;
		while (game->cfg->map[i])
		{
			free(game->cfg->map[i]);
			i++;
		}
		free(game->cfg->map);
	}
	free(game->cfg);
	game->cfg = NULL;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_map_and_textures(game);
	cleanup_sprites_and_doors(game);
	cleanup_cfg(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->mlx = NULL;
	game->img = NULL;
	game->frame = NULL;
	game->z_buffer = NULL;
}
