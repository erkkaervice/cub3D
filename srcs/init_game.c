/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:50:53 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_hook(t_game *game)
{
	cleanup_game(game);
	exit(0);
}

static int	init_mlx_and_win(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
	{
		cleanup_game(game);
		return (0);
	}
	mlx_hook(game->win, 17, 0, close_hook, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	return (1);
}

static int	init_img_and_addr(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		cleanup_game(game);
		return (0);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	if (!game->addr)
	{
		cleanup_game(game);
		return (0);
	}
	return (1);
}

static int	init_cfg_and_textures(t_game *game)
{
	game->cfg = mock_config();
	if (!game->cfg)
	{
		cleanup_game(game);
		return (0);
	}
	if (!load_textures(game))
	{
		cleanup_game(game);
		return (0);
	}
	return (1);
}

int	init_game(t_game *game)
{
	if (!init_mlx_and_win(game))
		return (0);
	if (!init_cfg_and_textures(game))
		return (0);
	if (!init_img_and_addr(game))
		return (0);
	init_dir_infos(game);
	init_player(game);
	mlx_loop_hook(game->mlx, render_frame, game);
	return (1);
}
