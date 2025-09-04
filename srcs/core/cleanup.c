/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:00:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_cfg_tex_paths(t_config *cfg)
{
	cfg->ceiling_color = NULL;
	cfg->floor_color = NULL;
	cfg->north_tex = NULL;
	cfg->south_tex = NULL;
	cfg->west_tex = NULL;
	cfg->east_tex = NULL;
	cfg->door_tex = NULL;
	cfg->sprite_tex_0 = NULL;
	cfg->sprite_tex_1 = NULL;
	cfg->sprite_tex_2 = NULL;
}

static void	cleanup_map_and_tex(t_game *g)
{
	if (!g)
		return ;
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->frame)
		mlx_delete_image(g->mlx, g->frame);
	if (g->z_buffer)
		free(g->z_buffer);
	free_tex(g, TEX_COUNT);
	cleanup_cfg_tex_paths(g->cfg);
}

static void	cleanup_sprites_and_doors(t_game *g)
{
	if (!g)
		return ;
	if (g->sprites)
	{
		free(g->sprites);
		g->sprites = NULL;
		g->num_sprites = 0;
	}
	if (g->doors)
	{
		free(g->doors);
		g->doors = NULL;
		g->num_doors = 0;
	}
}

static void	cleanup_cfg(t_game *g)
{
	int	i;

	if (!g || !g->cfg)
		return ;
	if (g->cfg->map)
	{
		i = 0;
		while (g->cfg->map[i])
			ft_free(&g->cfg->map[i++]);
		free(g->cfg->map);
	}
	cleanup_cfg_tex_paths(g->cfg);
	free(g->cfg);
	g->cfg = NULL;
}

void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
	cleanup_map_and_tex(g);
	cleanup_sprites_and_doors(g);
	cleanup_cfg(g);
	if (g->mlx)
		mlx_terminate(g->mlx);
	g->mlx = NULL;
	g->img = NULL;
	g->frame = NULL;
	g->z_buffer = NULL;
}
