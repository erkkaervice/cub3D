/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:44:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 15:02:56 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cfg_tex(t_config *cfg)
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
}

void	free_cfg(t_config **cfg_ptr)
{
	int			i;
	t_config	*cfg;

	if (!cfg_ptr || !*cfg_ptr)
		return ;
	cfg = *cfg_ptr;
	if (cfg->map)
	{
		i = 0;
		while (cfg->map[i])
			ft_free(&cfg->map[i++]);
		free(cfg->map);
	}
	if (cfg->sprite_tex)
	{
		i = 0;
		while (cfg->sprite_tex[i])
			ft_free(&cfg->sprite_tex[i++]);
		ft_free((char **)&cfg->sprite_tex);
	}
	free_cfg_tex(cfg);
	free(cfg);
	*cfg_ptr = NULL;
}

void	free_tex(t_game *g)
{
	int	i;

	if (!g)
		return ;
	i = 0;
	while (i < TEX_COUNT)
	{
		if (g->tex[i])
		{
			if (g->tex[i]->img)
			{
				mlx_delete_image(g->mlx, g->tex[i]->img);
				g->tex[i]->img = NULL;
			}
			if (g->tex[i]->tex)
			{
				mlx_delete_texture(g->tex[i]->tex);
				g->tex[i]->tex = NULL;
			}
			free(g->tex[i]);
			g->tex[i] = NULL;
		}
		i++;
	}
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	if (g->img)
	{
		mlx_delete_image(g->mlx, g->img);
		g->img = NULL;
	}
	if (g->front_buffer)
	{
		mlx_delete_image(g->mlx, g->front_buffer);
		g->front_buffer = NULL;
	}
	if (g->back_buffer)
	{
		mlx_delete_image(g->mlx, g->back_buffer);
		g->back_buffer = NULL;
	}
	if (g->z_buffer)
	{
		free(g->z_buffer);
		g->z_buffer = NULL;
	}
	free_tex(g);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
