/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:53:18 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_game *game, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (game->textures[i])
		{
			if (game->textures[i]->img)
				mlx_destroy_image(game->mlx, game->textures[i]->img);
			free(game->textures[i]);
			game->textures[i] = NULL;
		}
		i++;
	}
}

static void	cleanup_textures(t_game *game)
{
	if (!game || !game->cfg)
		return ;
	if (game->cfg->north_texture)
	{
		free(game->cfg->north_texture);
		game->cfg->north_texture = NULL;
	}
	if (game->cfg->south_texture)
	{
		free(game->cfg->south_texture);
		game->cfg->south_texture = NULL;
	}
	if (game->cfg->west_texture)
	{
		free(game->cfg->west_texture);
		game->cfg->west_texture = NULL;
	}
	if (game->cfg->east_texture)
	{
		free(game->cfg->east_texture);
		game->cfg->east_texture = NULL;
	}
	free_textures(game, 4);
}

static void	cleanup_map(t_game *game)
{
	int	i;

	if (!game || !game->cfg || !game->cfg->map)
		return ;
	i = 0;
	while (game->cfg->map[i])
	{
		free(game->cfg->map[i]);
		game->cfg->map[i] = NULL;
		i++;
	}
	free(game->cfg->map);
	game->cfg->map = NULL;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	cleanup_textures(game);
	cleanup_map(game);
	if (game->cfg)
		free(game->cfg);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
