/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:55:14 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/08 15:49:59 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_ray(t_ray *r, int axis)
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
	int		ret;

	if (r->map_x < 0 || r->map_x >= map_w
		|| r->map_y < 0 || r->map_y >= map_h)
		return (-1);
	tile = g->cfg->map[r->map_y][r->map_x];
	if (tile == TILE_WALL)
		return (1);
	if (tile == TILE_DOOR)
	{
		ret = handle_door(g, r);
		return (ret);
	}
	return (-1);
}

int	get_tex_x(t_game *g, t_ray *r, float wall_x, int tex_id)
{
	int			tex_x;
	t_tex		*t;

	if (tex_id < 0 || tex_id >= TEX_COUNT)
		return (0);
	t = g->tex[tex_id];
	if (!t || !t->image)
		return (0);
	tex_x = (int)(wall_x * (float)t->width);
	if ((r->side == AXIS_X && r->ray_dir_x > 0)
		|| (r->side == AXIS_Y && r->ray_dir_y < 0))
		tex_x = t->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= t->width)
		tex_x = t->width - 1;
	return (tex_x);
}

int	perform_dda(t_game *g, t_ray *r, int x)
{
	int		map_w;
	int		map_h;
	int		step_count;
	int		ret;

	map_w = map_dim(&g->cfg->map[0], MAP_DIM_WIDTH);
	map_h = map_dim(g->cfg->map, MAP_DIM_HEIGHT);
	step_count = 0;
	while (step_count < MAX_DDA_STEPS)
	{
		if (r->side_dist_x < r->side_dist_y)
			step_ray(r, AXIS_X);
		else
			step_ray(r, AXIS_Y);
		ret = handle_tile(g, r, map_w, map_h);
		if (ret != -1)
		{
			g->z_buffer[x] = r->perp_wall_dist;
			return (ret);
		}
		step_count++;
	}
	g->z_buffer[x] = r->perp_wall_dist;
	return (RAY_HIT_NONE);
}

void	raycast_column(t_game *g, int x)
{
	t_ray	r;
	t_wall	w;
	int		t;
	int		hit;

	g->z_buffer[x] = INFINITY;
	init_ray_basic(g, x, &r);
	init_ray_steps(g, &r);
	r.perp_wall_dist = RAY_MAX_DIST;
	hit = perform_dda(g, &r, x);
	if (hit == RAY_HIT_NONE)
		return ;
	if (hit == RAY_HIT_DOOR && door_hit(g, &r, &w, &t) == 0)
	{
		calculate_wall(g, &r, &w);
		t = TEX_DOOR;
	}
	else if (hit == RAY_HIT_WALL)
	{
		calculate_wall(g, &r, &w);
		t = get_tex_index(r.side, r.ray_dir_x, r.ray_dir_y);
	}
	w.tex_x = get_tex_x(g, &r, w.wall_x, t);
	draw_column(g, &w, x, t);
}
