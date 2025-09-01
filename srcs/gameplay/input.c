/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:25:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/29 17:27:02 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(t_input *input, int key, int value)
{
	if (key == MLX_KEY_W)
		input->w = value;
	else if (key == MLX_KEY_A)
		input->a = value;
	else if (key == MLX_KEY_S)
		input->s = value;
	else if (key == MLX_KEY_D)
		input->d = value;
	else if (key == MLX_KEY_LEFT)
		input->left = value;
	else if (key == MLX_KEY_RIGHT)
		input->right = value;
	else if (key == MLX_KEY_LEFT_SHIFT || key == MLX_KEY_RIGHT_SHIFT)
		input->shift = value;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == KEY_MINIMAP_TOGGLE)
			game->minimap_visible = !game->minimap_visible;
		else if (keydata.key == KEY_FPS_TOGGLE)
			game->fps_visible = !game->fps_visible;
		else if (keydata.key == MLX_KEY_E)
			toggle_door(game);
		else
			set_key(&game->input, keydata.key, 1);
	}
	else if (keydata.action == MLX_RELEASE)
		set_key(&game->input, keydata.key, 0);
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
