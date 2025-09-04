/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:02:25 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:14:25 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_id_for_hit(t_game *g, t_ray *r)
{
	char	cell;

	if (r->map_y < 0 || r->map_x < 0)
		return (-1);
	cell = g->cfg->map[r->map_y][r->map_x];
	if (cell == TILE_DOOR)
		return (TEX_DOOR);
	if (cell == TILE_WALL)
		return (get_tex_index(r->side, r->ray_dir_x, r->ray_dir_y));
	return (-1);
}

void	toggle_door(t_game *g)
{
	int		i;
	int		x;
	int		y;
	float	px;
	float	py;

	px = g->player_x;
	py = g->player_y;
	x = (int)(px + g->dir_x * DOOR_TOGGLE_RANGE);
	y = (int)(py + g->dir_y * DOOR_TOGGLE_RANGE);
	i = -1;
	while (++i < g->num_doors)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
		{
			if (!g->doors[i].is_opening)
				if (px > (float)x && px < (float)(x + 1)
					&& py > (float)y && py < (float)(y + 1))
					return ;
			g->doors[i].is_opening = !g->doors[i].is_opening;
			break ;
		}
	}
}

void	update_doors(t_game *g)
{
	int	i;

	if (!g || !g->doors)
		return ;
	i = 0;
	while (i < g->num_doors)
	{
		if (g->doors[i].is_opening)
		{
			g->doors[i].open_ratio += DOOR_OPEN_SPEED;
			if (g->doors[i].open_ratio > DOOR_OPEN_RATIO_FULL)
				g->doors[i].open_ratio = DOOR_OPEN_RATIO_FULL;
		}
		else
		{
			g->doors[i].open_ratio -= DOOR_OPEN_SPEED;
			if (g->doors[i].open_ratio < DOOR_OPEN_RATIO_START)
				g->doors[i].open_ratio = DOOR_OPEN_RATIO_START;
		}
		i++;
	}
}

int	handle_door(t_game *g, t_ray *r)
{
	int		d_idx;
	float	open_ratio;

	d_idx = find_door_index(g, r->map_x, r->map_y);
	if (d_idx < 0)
		return (RAY_HIT_DOOR);
	open_ratio = g->doors[d_idx].open_ratio;
	if (open_ratio > DOOR_OPEN_RATIO_START && open_ratio < DOOR_OPEN_RATIO_FULL)
		return (-1);
	if (open_ratio >= DOOR_OPEN_RATIO_FULL)
		return (-1);
	return (RAY_HIT_DOOR);
}

int	door_hit(t_game *g, t_ray *r, t_wall *w, int *tex_id)
{
	int		d_idx;
	float	offset;

	d_idx = find_door_index(g, r->map_x, r->map_y);
	if (d_idx < 0)
		return (0);
	offset = g->doors[d_idx].open_ratio;
	if (r->side == AXIS_X)
		r->side_dist_x -= offset * r->step_x;
	else
		r->side_dist_y -= offset * r->step_y;
	calculate_wall(g, r, w);
	*tex_id = TEX_DOOR;
	return (1);
}
