/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:16:34 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/06 15:13:20 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move(const t_game *g, float x, float y)
{
	int		ix;
	int		iy;

	if (!g || !g->cfg || !g->cfg->map)
		return (0);
	ix = (int)x;
	iy = (int)y;
	if (x < 0.0f || y < 0.0f)
		return (0);
	if (iy >= g->cfg->map_h)
		return (0);
	if (ix >= g->cfg->map_w)
		return (0);
	if (tile_blocked(g, ix, iy))
		return (0);
	return (1);
}

void	move(t_game *g, float move_x, float move_y)
{
	float	len;

	len = move_x * move_x + move_y * move_y;
	if (len > 1e-6f && len > 1.0f)
	{
		len = sqrtf(len);
		move_x /= len;
		move_y /= len;
	}
	if (can_move(g, g->player_x, g->player_y + move_y))
		g->player_y += move_y;
	if (can_move(g, g->player_x + move_x, g->player_y))
		g->player_x += move_x;
	if (g->player_x < 0.0f)
		g->player_x = 0.0f;
	if (g->player_y < 0.0f)
		g->player_y = 0.0f;
}

void	rotate(t_game *g, float angle)
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

void	calc_move_vec(t_game *g, float *dx, float *dy)
{
	*dx = 0.0f;
	*dy = 0.0f;
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

void	update_pos(t_game *g)
{
	float	mov;
	float	rot;
	float	dx;
	float	dy;

	if (g->input.run)
		mov = PLAYER_RUN_SPEED;
	else
		mov = PLAYER_WALK_SPEED;
	rot = PLAYER_ROT_SPEED;
	dx = 0.0f;
	dy = 0.0f;
	calc_move_vec(g, &dx, &dy);
	move(g, dx * mov, dy * mov);
	if (g->input.rotate_left)
		rotate(g, -rot);
	if (g->input.rotate_right)
		rotate(g, rot);
}
