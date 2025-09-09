/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/09 22:10:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config_textures(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->ceiling_color)
		ft_free(&cfg->ceiling_color);
	if (cfg->floor_color)
		ft_free(&cfg->floor_color);
	if (cfg->north_tex)
		ft_free(&cfg->north_tex);
	if (cfg->south_tex)
		ft_free(&cfg->south_tex);
	if (cfg->west_tex)
		ft_free(&cfg->west_tex);
	if (cfg->east_tex)
		ft_free(&cfg->east_tex);
	if (cfg->door_tex)
		ft_free(&cfg->door_tex);
	if (cfg->sprite_tex_0)
		ft_free(&cfg->sprite_tex_0);
	if (cfg->sprite_tex_1)
		ft_free(&cfg->sprite_tex_1);
	if (cfg->sprite_tex_2)
		ft_free(&cfg->sprite_tex_2);
}

void	free_config(t_config **cfg_ptr)
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
			ft_free(&cfg->map[i++]);
		free(cfg->map);
	}
	free_config_textures(cfg);
	free(cfg);
	*cfg_ptr = NULL;
}

void	free_textures(t_game *g, int count)
{
	int	i;

	if (!g || !g->tex)
		return ;
	i = 0;
	while (i < count)
	{
		if (g->tex[i])
		{
			if (g->tex[i]->img)
				mlx_delete_texture(g->tex[i]->img);
			free(g->tex[i]);
			g->tex[i] = NULL;
		}
		i++;
	}
}

static void	free_game_resources(t_game *g)
{
	if (!g)
		return ;
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->frame)
		mlx_delete_image(g->mlx, g->frame);
	if (g->z_buffer)
		free(g->z_buffer);
	if (g->sprites)
		free(g->sprites);
	if (g->doors)
		free(g->doors);
	free_textures(g, TEX_COUNT);
}

void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
	free_game_resources(g);
	if (g->cfg)
		free_config(&g->cfg);
	if (g->mlx)
		mlx_terminate(g->mlx);
	g->mlx = NULL;
	g->img = NULL;
	g->frame = NULL;
	g->z_buffer = NULL;
	g->sprites = NULL;
	g->doors = NULL;
}
