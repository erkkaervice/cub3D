/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:27:01 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 17:13:22 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_door_index(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

float	get_wall_x_with_door(t_game *game, t_ray *ray, float perp_wall_dist)
{
	float	wall_x;
	int		door_idx;
	float	open_ratio;

	if (ray->side == AXIS_X)
		wall_x = game->player_y + perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_x + perp_wall_dist * ray->ray_dir_x;
	wall_x -= floorf(wall_x);
	if (game->cfg->map[ray->map_y][ray->map_x] != TILE_DOOR)
		return (wall_x);
	door_idx = find_door_index(game, ray->map_x, ray->map_y);
	if (door_idx < 0)
		return (wall_x);
	open_ratio = game->doors[door_idx].open_ratio;
	if (ray->side == AXIS_X)
		wall_x -= open_ratio * ray->step_x;
	else
		wall_x -= open_ratio * ray->step_y;
	if (wall_x < 0.0f)
		wall_x += 1.0f;
	if (wall_x > 1.0f)
		wall_x -= 1.0f;
	return (wall_x);
}

int	count_doors(t_game *game)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = -1;
	while (game->cfg->map[++y])
	{
		x = -1;
		while (game->cfg->map[y][++x])
			if (game->cfg->map[y][x] == TILE_DOOR)
				count++;
	}
	return (count);
}

int	fill_doors(t_game *game)
{
	int	y;
	int	x;
	int	idx;

	idx = 0;
	y = -1;
	while (game->cfg->map[++y])
	{
		x = -1;
		while (game->cfg->map[y][++x])
		{
			if (game->cfg->map[y][x] == TILE_DOOR)
			{
				game->doors[idx].x = x;
				game->doors[idx].y = y;
				game->doors[idx].is_opening = 0;
				game->doors[idx].open_ratio = DOOR_OPEN_RATIO_START;
				idx++;
			}
		}
	}
	return (1);
}

int	count_and_fill_doors(t_game *game)
{
	int	count;

	count = count_doors(game);
	game->doors = malloc(sizeof(t_door) * count);
	if (!game->doors)
		return (0);
	game->num_doors = count;
	fill_doors(game);
	return (1);
}
