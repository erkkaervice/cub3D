/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:52:06 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 19:20:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*map_config(char *f)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	ft_bzero(cfg, sizeof(t_config));
	if (!map_parsing(cfg, f))
		return (free_partial_config(&cfg), NULL);
	cfg->door_tex = ft_strdup(TEX_PATH_DOOR);
	cfg->sprite_tex_0 = ft_strdup(TEX_PATH_SPRITE_0);
	cfg->sprite_tex_1 = ft_strdup(TEX_PATH_SPRITE_1);
	cfg->sprite_tex_2 = ft_strdup(TEX_PATH_SPRITE_2);
	if (!cfg->door_tex || !cfg->sprite_tex_0
		|| !cfg->sprite_tex_1 || !cfg->sprite_tex_2)
		return (free_partial_config(&cfg), NULL);
	return (cfg);
}

int	map_dim(char **map, int mode)
{
	if (!map)
		return (0);
	if (mode == MAP_DIM_HEIGHT)
		return (ft_array_len((void **)map));
	else if (mode == MAP_DIM_WIDTH)
	{
		if (!map[0])
			return (0);
		return ((int)ft_strlen(map[0]));
	}
	return (0);
}

int	is_wall_or_door(t_game *g, int x, int y)
{
	int		h;
	char	t;
	int		d_idx;

	h = map_dim(g->cfg->map, MAP_DIM_HEIGHT);
	if (y < 0 || y >= h)
		return (1);
	if (x < 0 || x >= map_dim(&g->cfg->map[y], MAP_DIM_WIDTH))
		return (1);
	t = g->cfg->map[y][x];
	if (t == TILE_WALL)
		return (1);
	if (t == TILE_DOOR)
	{
		d_idx = find_door_index(g, x, y);
		if (d_idx < 0)
			return (1);
		if (g->doors[d_idx].open_ratio < DOOR_OPEN_RATIO_FULL)
			return (1);
	}
	return (0);
}

static float	wall_maths(t_game *g, t_ray *r, float *wx)
{
	float	perp;

	if (r->side == AXIS_X)
		perp = (r->map_x - g->player_x
				+ (1 - r->step_x) * RAY_HALF_TILE_OFFSET) / r->ray_dir_x;
	else
		perp = (r->map_y - g->player_y
				+ (1 - r->step_y) * RAY_HALF_TILE_OFFSET) / r->ray_dir_y;
	if (perp < RAY_MIN_PERP_DIST)
		perp = RAY_MIN_PERP_DIST;
	if (r->side == AXIS_X)
		*wx = g->player_y + perp * r->ray_dir_y;
	else
		*wx = g->player_x + perp * r->ray_dir_x;
	*wx -= (int)*wx;
	return (perp);
}

void	calculate_wall(t_game *g, t_ray *r, t_wall *w)
{
	float	perp;
	int		h;
	int		ds;
	int		de;
	float	wx;

	perp = wall_maths(g, r, &wx);
	h = (int)(g->win_height / perp);
	if (h < 1)
		h = 1;
	ds = -h / 2 + g->win_height / 2;
	if (ds < 0)
		ds = 0;
	de = h / 2 + g->win_height / 2;
	if (de >= g->win_height)
		de = g->win_height - 1;
	w->perp_wall_dist = perp;
	w->line_height = h;
	w->draw_start = ds;
	w->draw_end = de;
	w->wall_x = wx;
}
