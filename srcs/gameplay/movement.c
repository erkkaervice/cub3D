/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:29:29 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 17:30:40 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move(t_game *game, float x, float y)
{
	int		ix;
	int		iy;

	ix = (int)x;
	iy = (int)y;
	if (x < 0.0f || y < 0.0f)
		return (0);
	if (iy >= map_dim(game->cfg->map, MAP_DIM_HEIGHT))
		return (0);
	if (ix >= map_dim(&game->cfg->map[iy], MAP_DIM_WIDTH))
		return (0);
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
	if (game->input.move_forward)
	{
		*dx += game->dir_x;
		*dy += game->dir_y;
	}
	if (game->input.move_backward)
	{
		*dx -= game->dir_x;
		*dy -= game->dir_y;
	}
	if (game->input.move_left)
	{
		*dx -= game->plane_x;
		*dy -= game->plane_y;
	}
	if (game->input.move_right)
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

	move = PLAYER_WALK_SPEED;
	if (game->input.run)
		move = PLAYER_RUN_SPEED;
	rot = PLAYER_ROT_SPEED;
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
	if (game->input.rotate_left)
		rotate_player(game, -rot);
	if (game->input.rotate_right)
		rotate_player(game, rot);
}
