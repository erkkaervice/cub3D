/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:25:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:54:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.w = 1;
	else if (keycode == KEY_A)
		game->input.a = 1;
	else if (keycode == KEY_S)
		game->input.s = 1;
	else if (keycode == KEY_D)
		game->input.d = 1;
	else if (keycode == KEY_LEFT)
		game->input.left = 1;
	else if (keycode == KEY_RIGHT)
		game->input.right = 1;
	else if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.w = 0;
	else if (keycode == KEY_A)
		game->input.a = 0;
	else if (keycode == KEY_S)
		game->input.s = 0;
	else if (keycode == KEY_D)
		game->input.d = 0;
	else if (keycode == KEY_LEFT)
		game->input.left = 0;
	else if (keycode == KEY_RIGHT)
		game->input.right = 0;
	return (0);
}
