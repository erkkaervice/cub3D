/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:29:29 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:50:35 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_game *game, float x, float y)
{
	int	ix;
	int	iy;

	if (x < 0 || y < 0)
		return (0);
	ix = (int)x;
	iy = (int)y;
	if (iy >= map_height(game->cfg->map) || ix >= map_width(game->cfg->map[0]))
		return (0);
	return (game->cfg->map[iy][ix] != '1');
}

static void	move_player(t_game *game, float dx, float dy, float speed)
{
	float	new_x;
	float	new_y;

	new_x = game->player_x + dx * speed;
	if (can_move(game, new_x, game->player_y))
		game->player_x = new_x;
	new_y = game->player_y + dy * speed;
	if (can_move(game, game->player_x, new_y))
		game->player_y = new_y;
}

static void	rotate_player(t_game *game, float angle)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void	update_player_position(t_game *game)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 0.05f;
	rot_speed = 0.03f;
	if (game->input.w == 1)
		move_player(game, game->dir_x, game->dir_y, move_speed);
	if (game->input.s == 1)
		move_player(game, -game->dir_x, -game->dir_y, move_speed);
	if (game->input.a == 1)
		move_player(game, -game->plane_x, -game->plane_y, move_speed);
	if (game->input.d == 1)
		move_player(game, game->plane_x, game->plane_y, move_speed);
	if (game->input.left == 1)
		rotate_player(game, rot_speed);
	if (game->input.right == 1)
		rotate_player(game, -rot_speed);
}
