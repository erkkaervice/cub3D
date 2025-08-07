/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:25:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 18:25:23 by eala-lah         ###   ########.fr       */
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
