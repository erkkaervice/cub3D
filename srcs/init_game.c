/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/29 17:22:04 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_hook(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
}

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (width <= 0 || height <= 0)
		return ;
	game->win_width = width;
	game->win_height = height;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, width, height);
	if (!game->img)
		exit(1);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		exit(1);
	game->needs_blit = 1;
}

static int	init_mlx_win_and_img(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	if (!game->mlx)
		return (0);
	game->frame = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame)
		return (0);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (0);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (0);
	game->win_width = WIDTH;
	game->win_height = HEIGHT;
	game->needs_blit = 1;
	mlx_resize_hook(game->mlx, resize_hook, game);
	return (1);
}

static int	init_game_resources(t_game *game, char *filename)
{
	int	i;

	game->cfg = mock_config(filename);
	if (!game->cfg)
		return (0);
	if (!load_textures(game))
		return (0);
	parse_sprites(game);
	init_doors(game);
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		return (0);
	i = 0;
	while (i < WIDTH)
	{
		game->z_buffer[i] = 0.0f;
		i++;
	}
	return (1);
}

int	init_game(t_game *game, char *filename)
{
	if (!init_mlx_win_and_img(game))
		return (0);
	if (!init_game_resources(game, filename))
		return (0);
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
