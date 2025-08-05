/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/05 17:09:04 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_hook(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
}

static int	init_mlx_and_win(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	return (game->mlx != NULL);
}

static int	init_img(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (0);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (0);
	return (1);
}

static int	init_cfg_and_textures(t_game *game)
{
	game->cfg = mock_config();
	if (!game->cfg)
		return (0);
	if (!load_textures(game))
		return (0);
	return (1);
}

int	init_game(t_game *game)
{
	if (!init_mlx_and_win(game))
		return (0);
	if (!init_cfg_and_textures(game))
		return (0);
	if (!init_img(game))
		return (0);
	init_dir_infos(game);
	init_player(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_close_hook(game->mlx, close_hook, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	return (1);
}
