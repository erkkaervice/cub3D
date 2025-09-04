/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:29:29 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:09:30 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move(t_game *g, float x, float y)
{
	int		ix;
	int		iy;

	ix = (int)x;
	iy = (int)y;
	if (x < 0.0f || y < 0.0f)
		return (0);
	if (iy >= map_dim(g->cfg->map, MAP_DIM_HEIGHT))
		return (0);
	if (ix >= map_dim(&g->cfg->map[iy], MAP_DIM_WIDTH))
		return (0);
	if (is_wall_or_door(g, ix, iy))
		return (0);
	return (1);
}

static void	move_player(t_game *g, float dx, float dy, float speed)
{
	float	new_x;
	float	new_y;

	new_x = g->player_x + dx * speed;
	new_y = g->player_y + dy * speed;
	if (can_move(g, g->player_x, new_y))
		g->player_y = new_y;
	if (can_move(g, new_x, g->player_y))
		g->player_x = new_x;
}

static void	rotate_player(t_game *g, float angle)
{
	float	cos_a;
	float	sin_a;
	float	old_dir_x;
	float	old_plane_x;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	old_dir_x = g->dir_x;
	old_plane_x = g->plane_x;
	g->dir_x = old_dir_x * cos_a - g->dir_y * sin_a;
	g->dir_y = old_dir_x * sin_a + g->dir_y * cos_a;
	g->plane_x = old_plane_x * cos_a - g->plane_y * sin_a;
	g->plane_y = old_plane_x * sin_a + g->plane_y * cos_a;
}

void	update_movement_vector(t_game *g, float *dx, float *dy)
{
	if (g->input.move_forward)
	{
		*dx += g->dir_x;
		*dy += g->dir_y;
	}
	if (g->input.move_backward)
	{
		*dx -= g->dir_x;
		*dy -= g->dir_y;
	}
	if (g->input.move_left)
	{
		*dx -= g->plane_x;
		*dy -= g->plane_y;
	}
	if (g->input.move_right)
	{
		*dx += g->plane_x;
		*dy += g->plane_y;
	}
}

void	update_player_position(t_game *g)
{
	float	move;
	float	rot;
	float	dx;
	float	dy;
	float	len;

	move = PLAYER_WALK_SPEED;
	if (g->input.run)
		move = PLAYER_RUN_SPEED;
	rot = PLAYER_ROT_SPEED;
	dx = 0.0f;
	dy = 0.0f;
	update_movement_vector(g, &dx, &dy);
	len = dx * dx + dy * dy;
	if (len > 1.0f)
	{
		len = sqrtf(len);
		dx /= len;
		dy /= len;
	}
	move_player(g, dx, dy, move);
	if (g->input.rotate_left)
		rotate_player(g, -rot);
	if (g->input.rotate_right)
		rotate_player(g, rot);
}
