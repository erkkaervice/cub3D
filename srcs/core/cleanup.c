/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 20:00:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_cfg_textures_paths(t_config *cfg)
{
	cfg->ceiling_color = NULL;
	cfg->floor_color = NULL;
	cfg->north_texture = NULL;
	cfg->south_texture = NULL;
	cfg->west_texture = NULL;
	cfg->east_texture = NULL;
	cfg->door_texture = NULL;
	cfg->sprite_texture_0 = NULL;
	cfg->sprite_texture_1 = NULL;
	cfg->sprite_texture_2 = NULL;
}

static void	cleanup_map_and_textures(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->frame)
		mlx_delete_image(game->mlx, game->frame);
	if (game->z_buffer)
		free(game->z_buffer);
	free_textures(game, TEXTURE_COUNT);
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
	cleanup_cfg_textures_paths(game->cfg);
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
