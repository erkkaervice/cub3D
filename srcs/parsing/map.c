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

t_config	*map_config(char *filename)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	ft_bzero(cfg, sizeof(t_config));
	if (!map_parsing(cfg, filename))
		return (free_partial_config(&cfg), NULL);
	cfg->door_texture = ft_strdup(TEX_PATH_DOOR);
	cfg->sprite_texture_0 = ft_strdup(TEX_PATH_SPRITE_0);
	cfg->sprite_texture_1 = ft_strdup(TEX_PATH_SPRITE_1);
	cfg->sprite_texture_2 = ft_strdup(TEX_PATH_SPRITE_2);
	if (!cfg->door_texture || !cfg->sprite_texture_0
		|| !cfg->sprite_texture_1 || !cfg->sprite_texture_2)
		return (free_partial_config(&cfg), NULL);
	return (cfg);
}

int	map_dim(char **map, int mode)
{
	int	i;
	int	len;

	if (!map)
		return (0);
	if (mode == MAP_DIM_HEIGHT)
	{
		i = 0;
		while (map[i])
			i++;
		return (i);
	}
	else if (mode == MAP_DIM_WIDTH)
	{
		if (!map[0])
			return (0);
		len = 0;
		while (map[0][len])
			len++;
		return (len);
	}
	return (0);
}

int	is_wall_or_door(t_game *game, int x, int y)
{
	int		height;
	char	tile;
	int		door_idx;

	height = map_dim(game->cfg->map, MAP_DIM_HEIGHT);
	if (y < 0 || y >= height)
		return (1);
	if (x < 0 || x >= map_dim(&game->cfg->map[y], MAP_DIM_WIDTH))
		return (1);
	tile = game->cfg->map[y][x];
	if (tile == TILE_WALL)
		return (1);
	if (tile == TILE_DOOR)
	{
		door_idx = find_door_index(game, x, y);
		if (door_idx < 0)
			return (1);
		if (game->doors[door_idx].open_ratio < DOOR_OPEN_RATIO_FULL)
			return (1);
	}
	return (0);
}

static float	wall_maths(t_game *game, t_ray *ray, float *wx)
{
	float	perp_dist;

	if (ray->side == AXIS_X)
		perp_dist = (ray->map_x - game->player_x
				+ (1 - ray->step_x) * RAY_HALF_TILE_OFFSET) / ray->ray_dir_x;
	else
		perp_dist = (ray->map_y - game->player_y
				+ (1 - ray->step_y) * RAY_HALF_TILE_OFFSET) / ray->ray_dir_y;
	if (perp_dist < RAY_MIN_PERP_DIST)
		perp_dist = RAY_MIN_PERP_DIST;
	if (ray->side == AXIS_X)
		*wx = game->player_y + perp_dist * ray->ray_dir_y;
	else
		*wx = game->player_x + perp_dist * ray->ray_dir_x;
	*wx -= (int)*wx;
	return (perp_dist);
}

void	calculate_wall(t_game *game, t_ray *ray, t_wall *wall)
{
	float	perp;
	int		h;
	int		ds;
	int		de;
	float	wx;

	perp = wall_maths(game, ray, &wx);
	h = (int)(game->win_height / perp);
	if (h < 1)
		h = 1;
	ds = -h / 2 + game->win_height / 2;
	if (ds < 0)
		ds = 0;
	de = h / 2 + game->win_height / 2;
	if (de >= game->win_height)
		de = game->win_height - 1;
	wall->perp_wall_dist = perp;
	wall->line_height = h;
	wall->draw_start = ds;
	wall->draw_end = de;
	wall->wall_x = wx;
}
