/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:19 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/25 15:07:30 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		file_valid(argv[1], ".cub", "/.cub");
		init_game_struct(&game);
		if (!init_game(&game, argv[1]))
		{
			cleanup_game(&game);
			return (1);
		}
		mlx_loop(game.mlx);
		cleanup_game(&game);
		return (0);
	}
	else
	{
		write(2, "Error\n", 6);
		return (1);
	}
}
