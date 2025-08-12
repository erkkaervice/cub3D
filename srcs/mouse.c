/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:53:27 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/12 18:13:48 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_init(t_game *game)
{
	game->mouse.dx = 0.0;
	game->mouse.sensitivity = MOUSE_SENSITIVITY;
	game->mouse.prev_x = MOUSE_START_X;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->mlx, MOUSE_START_X, MOUSE_START_Y);
}

void	mouse_move(double x, double y, void *param)
{
	t_game	*game;
	double	diff;

	(void)y;
	game = (t_game *)param;
	diff = x - game->mouse.prev_x;
	game->mouse.dx += diff;
	game->mouse.prev_x = MOUSE_START_X;
	mlx_set_mouse_pos(game->mlx, MOUSE_START_X, MOUSE_START_Y);
}

void	apply_mouse_look(t_game *game, double frame_time)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	if (game->mouse.dx != 0.0)
	{
		rot = (game->mouse.dx * game->mouse.sensitivity) * frame_time
			* MOUSE_FRAME_MULTIPLIER;
		old_dir_x = game->dir_x;
		old_plane_x = game->plane_x;
		game->dir_x = game->dir_x * cos(rot) - game->dir_y * sin(rot);
		game->dir_y = old_dir_x * sin(rot) + game->dir_y * cos(rot);
		game->plane_x = game->plane_x * cos(rot) - game->plane_y * sin(rot);
		game->plane_y = old_plane_x * sin(rot) + game->plane_y * cos(rot);
		game->mouse.dx *= MOUSE_DAMPING;
		if (fabs(game->mouse.dx) < MOUSE_DX_THRESHOLD)
			game->mouse.dx = 0.0;
	}
}
