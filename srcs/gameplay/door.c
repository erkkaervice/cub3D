/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:02:25 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/01 15:54:29 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_id_for_hit(t_game *game, t_ray *ray)
{
	char	cell;

	if (ray->map_y < 0 || ray->map_x < 0)
		return (-1);
	cell = game->cfg->map[ray->map_y][ray->map_x];
	if (cell == TILE_DOOR)
		return (TEX_DOOR);
	if (cell == TILE_WALL)
		return (get_texture_index(ray->side, ray->ray_dir_x, ray->ray_dir_y));
	return (-1);
}

void	toggle_door(t_game *game)
{
	int		i;
	int		x;
	int		y;
	float	px;
	float	py;

	px = game->player_x;
	py = game->player_y;
	x = (int)(px + game->dir_x * DOOR_TOGGLE_RANGE);
	y = (int)(py + game->dir_y * DOOR_TOGGLE_RANGE);
	i = -1;
	while (++i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
		{
			if (!game->doors[i].is_opening)
				if (px > (float)x && px < (float)(x + 1)
					&& py > (float)y && py < (float)(y + 1))
					return ;
			game->doors[i].is_opening = !game->doors[i].is_opening;
			break ;
		}
	}
}

void	update_doors(t_game *game)
{
	int	i;

	if (!game || !game->doors)
		return ;
	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].is_opening)
		{
			game->doors[i].open_ratio += DOOR_OPEN_SPEED;
			if (game->doors[i].open_ratio > DOOR_OPEN_FULL)
				game->doors[i].open_ratio = DOOR_OPEN_FULL;
		}
		else
		{
			game->doors[i].open_ratio -= DOOR_OPEN_SPEED;
			if (game->doors[i].open_ratio < DOOR_INITIAL_OPEN_RATIO)
				game->doors[i].open_ratio = DOOR_INITIAL_OPEN_RATIO;
		}
		i++;
	}
}

int	handle_door(t_game *game, t_ray *ray)
{
	int		door_idx;
	float	open_ratio;

	door_idx = find_door_index(game, ray->map_x, ray->map_y);
	if (door_idx < 0)
		return (HIT_DOOR);
	open_ratio = game->doors[door_idx].open_ratio;
	if (open_ratio > DOOR_INITIAL_OPEN_RATIO && open_ratio < DOOR_OPEN_FULL)
		return (-1);
	if (open_ratio >= DOOR_OPEN_FULL)
		return (-1);
	return (HIT_DOOR);
}

int	door_hit(t_game *game, t_ray *ray, t_wall *wall, int *tex_id)
{
	int		door_index;
	float	offset;

	door_index = find_door_index(game, ray->map_x, ray->map_y);
	if (door_index < 0)
		return (0);
	offset = game->doors[door_index].open_ratio;
	if (ray->side == AXIS_X)
		ray->side_dist_x -= offset * ray->step_x;
	else
		ray->side_dist_y -= offset * ray->step_y;
	calculate_wall(game, ray, wall);
	*tex_id = TEX_DOOR;
	return (1);
}
