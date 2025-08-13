/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 19:43:53 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_map(t_game *game)
{
	char	**map;
	int		i;

	if (!game || !game->cfg || !game->cfg->map)
		return ;
	map = game->cfg->map;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	game->cfg->map = NULL;
}

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

static void	cleanup_textures(t_game *game)
{
	t_config	*config;

	if (!game || !game->cfg)
		return ;
	config = game->cfg;
	free(config->north_texture);
	config->north_texture = NULL;
	free(config->south_texture);
	config->south_texture = NULL;
	free(config->west_texture);
	config->west_texture = NULL;
	free(config->east_texture);
	config->east_texture = NULL;
	free(config->door_texture);
	config->door_texture = NULL;
	free_textures(game, TEXTURE_COUNT);
}

static void	cleanup_sprites(t_game *game)
{
	if (!game || !game->sprites)
		return ;
	free(game->sprites);
	game->sprites = NULL;
	game->num_sprites = 0;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
	{
		mlx_delete_image(game->mlx, game->img);
		game->img = NULL;
	}
	cleanup_textures(game);
	cleanup_map(game);
	cleanup_sprites(game);
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
		game->num_doors = 0;
	}
	if (game->cfg)
	{
		free(game->cfg);
		game->cfg = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}
