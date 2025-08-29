/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:29:29 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/29 14:00:21 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move(t_game *game, float x, float y)
{
	int		ix;
	int		iy;
	int		height;

	height = map_height(game->cfg->map);
	if (x < 0.0f || y < 0.0f)
		return (0);
	if (y >= (float)height)
		return (0);
	if (x >= (float)map_width(game->cfg->map[(int)y]))
		return (0);
	ix = (int)x;
	iy = (int)y;
	if (is_wall_or_door(game, ix, iy))
		return (0);
	return (1);
}

static void	move_player(t_game *game, float dx, float dy, float speed)
{
	float	new_x;
	float	new_y;

	new_x = game->player_x + dx * speed;
	new_y = game->player_y + dy * speed;
	if (can_move(game, game->player_x, new_y))
		game->player_y = new_y;
	if (can_move(game, new_x, game->player_y))
		game->player_x = new_x;
}

static void	rotate_player(t_game *game, float angle)
{
	float	cos_a;
	float	sin_a;
	float	old_dir_x;
	float	old_plane_x;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = old_dir_x * cos_a - game->dir_y * sin_a;
	game->dir_y = old_dir_x * sin_a + game->dir_y * cos_a;
	game->plane_x = old_plane_x * cos_a - game->plane_y * sin_a;
	game->plane_y = old_plane_x * sin_a + game->plane_y * cos_a;
}

void	update_movement_vector(t_game *game, float *dx, float *dy)
{
	if (game->input.w == 1)
	{
		*dx += game->dir_x;
		*dy += game->dir_y;
	}
	if (game->input.s == 1)
	{
		*dx -= game->dir_x;
		*dy -= game->dir_y;
	}
	if (game->input.a == 1)
	{
		*dx -= game->plane_x;
		*dy -= game->plane_y;
	}
	if (game->input.d == 1)
	{
		*dx += game->plane_x;
		*dy += game->plane_y;
	}
}

void	update_player_position(t_game *game)
{
	float	move;
	float	rot;
	float	dx;
	float	dy;
	float	len;

	move = MOVE_SPEED;
	if (game->input.shift == 1)
		move = RUN_SPEED;
	rot = ROT_SPEED;
	dx = 0.0f;
	dy = 0.0f;
	update_movement_vector(game, &dx, &dy);
	len = dx * dx + dy * dy;
	if (len > 1.0f)
	{
		len = sqrtf(len);
		dx /= len;
		dy /= len;
	}
	move_player(game, dx, dy, move);
	if (game->input.left == 1)
		rotate_player(game, -rot);
	if (game->input.right == 1)
		rotate_player(game, rot);
}
