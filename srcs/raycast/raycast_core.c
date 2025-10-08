/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:26 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 14:30:59 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_ray(t_ray *r, int axis)
{
	if (axis == AXIS_X)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = AXIS_X;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = AXIS_Y;
	}
}

int	handle_tile(t_game *g, t_ray *r, int map_w, int map_h)
{
	char	tile;

	if (r->map_x < 0 || r->map_x >= map_w || r->map_y < 0 || r->map_y >= map_h)
		return (-1);
	tile = g->cfg->map[r->map_y][r->map_x];
	if (tile == TILE_WALL)
		return (RAY_HIT_WALL);
	if (tile == TILE_DOOR)
		return (RAY_HIT_DOOR);
	return (-1);
}

void	calc_perp_wall_dist(const t_game *g, t_ray *r, int x)
{
	if (r->side == AXIS_X)
		r->perp_wall_dist = (r->map_x - g->player_x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player_y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	((t_game *)g)->z_buffer[x] = r->perp_wall_dist;
}

int	raycast_dda(const t_game *g, t_ray *r, int x)
{
	int	map_w;
	int	map_h;
	int	step_count;
	int	ret;

	map_w = map_dim(&g->cfg->map[0], MAP_DIM_WIDTH);
	map_h = map_dim(g->cfg->map, MAP_DIM_HEIGHT);
	step_count = 0;
	ret = -1;
	while (step_count < MAX_DDA_STEPS)
	{
		if (r->side_dist_x < r->side_dist_y)
			step_ray(r, AXIS_X);
		else
			step_ray(r, AXIS_Y);
		ret = handle_tile((t_game *)g, r, map_w, map_h);
		if (ret != -1)
			break ;
		step_count++;
	}
	calc_perp_wall_dist(g, r, x);
	if (ret != -1)
		return (ret);
	return (RAY_HIT_NONE);
}

void	raycast_column(t_game *g, int x)
{
	t_ray	r;
	int		hit;

	init_ray(g, x, &r);
	init_ray_steps(g, &r);
	r.perp_wall_dist = RAY_MAX_DIST;
	g->z_buffer[x] = INFINITY;
	hit = raycast_dda(g, &r, x);
	if (hit == RAY_HIT_NONE)
		return ;
	if (hit == RAY_HIT_DOOR)
		door_draw_col(g, &r, x);
	else
		draw_wall(g, &r, x);
}
