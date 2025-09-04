/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:48:49 by dvlachos          #+#    #+#             */
/*   Updated: 2025/09/04 18:00:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex(t_game *g, int count)
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

static void	free_cfg_paths(t_config *cfg)
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
	cleanup_cfg_tex_paths(cfg);
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
			ft_free(&cfg->map[i++]);
		free(cfg->map);
		cfg->map = NULL;
	}
	free_cfg_paths(cfg);
	free(cfg);
	*cfg_ptr = NULL;
}
