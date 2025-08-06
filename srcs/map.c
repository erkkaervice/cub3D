/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:52:06 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/06 15:58:49 by eala-lah         ###   ########.fr       */
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

	height = map_height(game->cfg->map);
	if (y < 0 || y >= height)
		return (1);
	if (x < 0 || x >= map_width(game->cfg->map[y]))
		return (1);
	tile = game->cfg->map[y][x];
	if (tile == '1' || tile == 'D')
		return (1);
	return (0);
}

static float	wall_maths(t_game *game, t_ray *ray, float *wx)
{
	float	perp_dist;

	if (ray->side == 0)
		perp_dist = (ray->map_x - game->player_x
				+ (1 - ray->step_x) * 0.5f) / ray->ray_dir_x;
	else
		perp_dist = (ray->map_y - game->player_y
				+ (1 - ray->step_y) * 0.5f) / ray->ray_dir_y;
	if (perp_dist < 0.001f)
		perp_dist = 0.001f;
	if (ray->side == 0)
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
	wall->tex_x = get_tex_x(game, ray, wx);
}
