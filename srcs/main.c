/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:19 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/05 16:57:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_game	game;

	init_game_struct(&game);
	if (!init_game(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
