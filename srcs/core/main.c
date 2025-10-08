/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 13:48:26 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
	free_game(g);
	if (g->sprites)
	{
		free(g->sprites);
		g->sprites = NULL;
	}
	if (g->doors)
	{
		free(g->doors);
		g->doors = NULL;
	}
	if (g->cfg)
		free_cfg(&g->cfg);
	if (g->mlx)
	{
		mlx_terminate(g->mlx);
		g->mlx = NULL;
	}
	g->frame = NULL;
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <mapfile.cub>\n", 2);
		return (1);
	}
	cfg_check_file(av[1], ".cub", "/.cub");
	init_struct(&g);
	if (!init_game(&g, av[1]))
	{
		cleanup_game(&g);
		return (1);
	}
	mlx_loop(g.mlx);
	cleanup_game(&g);
	return (0);
}
