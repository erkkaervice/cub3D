/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:29:29 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/05 17:37:13 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_game *game, float x, float y)
{
	int		ix;
	int		iy;
	int		map_w;
	int		map_h;

	if (x < 0.0f || y < 0.0f)
		return (0);
	ix = (int)x;
	iy = (int)y;
	map_h = map_height(game->cfg->map);
	map_w = map_width(game->cfg->map[0]);
	if ((unsigned int)iy >= (unsigned int)map_h
		|| (unsigned int)ix >= (unsigned int)map_w)
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

void	update_player_position(t_game *game)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 0.05f;
	rot_speed = 0.03f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, game->dir_x, game->dir_y, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, -game->dir_x, -game->dir_y, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, -game->plane_x, -game->plane_y, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, game->plane_x, game->plane_y, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, rot_speed);
}
