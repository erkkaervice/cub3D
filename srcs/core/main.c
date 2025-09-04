/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:19 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:00:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	g;

	if (ac != 2)
		ft_error("Error");
	file_valid(av[1], ".cub", "/.cub");
	init_game_struct(&g);
	if (!init_game(&g, av[1]))
	{
		cleanup_game(&g);
		return (1);
	}
	mlx_loop(g.mlx);
	cleanup_game(&g);
	return (0);
}
