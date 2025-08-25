/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:52:06 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/25 15:37:19 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	map_width(char *row)
{
	int	i;

	if (!row)
		return (0);
	i = 0;
	while (row[i])
		i++;
	return (i);
}

int	is_wall_or_door(t_game *game, int x, int y)
{
	int		height;
	char	tile;
	int		door_idx;

	height = map_height(game->cfg->map);
	if (y < 0 || y >= height)
		return (1);
	if (x < 0 || x >= map_width(game->cfg->map[y]))
		return (1);
	tile = game->cfg->map[y][x];
	if (tile == TILE_WALL)
		return (1);
	if (tile == TILE_DOOR)
	{
		door_idx = find_door_index(game, x, y);
		if (door_idx < 0)
			return (1);
		if (game->doors[door_idx].open_ratio < 0.5f)
			return (1);
	}
	return (0);
}

static float	wall_maths(t_game *game, t_ray *ray, float *wx)
{
	float	perp_dist;

	if (ray->side == AXIS_X)
		perp_dist = (ray->map_x - game->player_x
				+ (1 - ray->step_x) * HALF_TILE_OFFSET) / ray->ray_dir_x;
	else
		perp_dist = (ray->map_y - game->player_y
				+ (1 - ray->step_y) * HALF_TILE_OFFSET) / ray->ray_dir_y;
	if (perp_dist < MIN_PERP_DIST)
		perp_dist = MIN_PERP_DIST;
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
	h = (int)(HEIGHT / perp);
	if (h < 1)
		h = 1;
	ds = -h / 2 + HEIGHT / 2;
	if (ds < 0)
		ds = 0;
	de = h / 2 + HEIGHT / 2;
	if (de >= HEIGHT)
		de = HEIGHT - 1;
	wall->perp_wall_dist = perp;
	wall->line_height = h;
	wall->draw_start = ds;
	wall->draw_end = de;
	wall->wall_x = wx;
}
