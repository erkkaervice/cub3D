/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:02:25 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/09 15:02:57 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_door_index(t_game *g, int x, int y)
{
	int	i;

	if (!g || !g->doors)
		return (-1);
	i = 0;
	while (i < g->num_doors)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

float	get_wall_x_with_door(t_game *g, t_ray *r, float perp_wall_dist)
{
	float	wall_x;
	int		i;
	float	open_ratio;

	if (r->side == AXIS_X)
		wall_x = g->player_y + perp_wall_dist * r->ray_dir_y;
	else
		wall_x = g->player_x + perp_wall_dist * r->ray_dir_x;
	wall_x -= floorf(wall_x);
	if (g->cfg->map[r->map_y][r->map_x] != TILE_DOOR)
		return (wall_x);
	i = find_door_index(g, r->map_x, r->map_y);
	if (i < 0)
		return (wall_x);
	open_ratio = g->doors[i].open_ratio;
	if (r->side == AXIS_X)
		wall_x -= open_ratio * r->step_x;
	else
		wall_x -= open_ratio * r->step_y;
	if (wall_x < 0.0f)
		wall_x += 1.0f;
	if (wall_x > 1.0f)
		wall_x -= 1.0f;
	return (wall_x);
}

int	count_doors(t_game *g)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (g->cfg->map[y])
	{
		x = 0;
		while (g->cfg->map[y][x])
		{
			if (g->cfg->map[y][x] == TILE_DOOR)
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

int	fill_doors(t_game *g)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (g->cfg->map[y])
	{
		x = 0;
		while (g->cfg->map[y][x])
		{
			if (g->cfg->map[y][x] == TILE_DOOR)
			{
				g->doors[i].x = x;
				g->doors[i].y = y;
				g->doors[i].is_opening = 0;
				g->doors[i].open_ratio = DOOR_OPEN_RATIO_START;
				i++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	count_and_fill_doors(t_game *g)
{
	int	i;

	i = count_doors(g);
	g->doors = ft_calloc(i, sizeof(t_door));
	if (!g->doors)
		return (0);
	g->num_doors = i;
	fill_doors(g);
	return (1);
}
