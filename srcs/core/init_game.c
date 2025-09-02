/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 19:14:42 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_hook(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
}

static void	resize_hook(int32_t w, int32_t h, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (w <= 0 || h <= 0)
		return ;
	game->win_width = w;
	game->win_height = h;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, w, h);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		exit(1);
	game->needs_blit = 1;
}

static int	init_mlx_win_and_img(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (!game->mlx)
		return (0);
	game->frame = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->frame || !game->img
		|| mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		if (game->img)
			mlx_delete_image(game->mlx, game->img);
		if (game->frame)
			mlx_delete_image(game->mlx, game->frame);
		mlx_terminate(game->mlx);
		return (0);
	}
	game->win_width = WINDOW_WIDTH;
	game->win_height = WINDOW_HEIGHT;
	game->needs_blit = 1;
	mlx_resize_hook(game->mlx, resize_hook, game);
	return (1);
}

static int	init_game_resources(t_game *game, char *filename)
{
	int	i;

	game->cfg = map_config(filename);
	if (!game->cfg || !load_textures(game))
	{
		free_partial_config(&game->cfg);
		return (0);
	}
	parse_sprites(game);
	init_doors(game);
	game->z_buffer = malloc(sizeof(float) * game->win_width);
	if (!game->z_buffer)
	{
		free_partial_config(&game->cfg);
		free_textures(game, TEXTURE_COUNT);
		return (0);
	}
	i = -1;
	while (++i < game->win_width)
		game->z_buffer[i] = 0.0f;
	return (1);
}

int	init_game(t_game *game, char *filename)
{
	if (!init_mlx_win_and_img(game))
		return (0);
	if (!init_game_resources(game, filename))
	{
		cleanup_game(game);
		return (0);
	}
	init_mouse(game);
	mlx_cursor_hook(game->mlx, mouse_move, game);
	init_dir_infos(game);
	init_player(game);
	game->minimap_visible = 0;
	game->fps_visible = 0;
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_close_hook(game->mlx, close_hook, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	return (1);
}
