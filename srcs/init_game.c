/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 18:17:36 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_hook(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
}

static int	init_mlx_win_and_img(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (0);
	if (mlx_image_to_window(game->mlx, game->img,
			WINDOW_IMG_POS_X, WINDOW_IMG_POS_Y) < 0)
		return (0);
	return (1);
}

static int	init_cfg_textures_and_doors(t_game *game, char *filename)
{
	game->cfg = mock_config(filename);
	if (!game->cfg)
		return (0);
	init_doors(game);
	parse_sprites(game);
	if (!load_textures(game))
		return (0);
	return (1);
}

static void	init_z_buffer(float *z_buffer, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		z_buffer[i] = 0.0f;
		i++;
	}
}

int	init_game(t_game *game, char *filename)
{
	if (!init_mlx_win_and_img(game))
		return (0);
	if (!init_cfg_textures_and_doors(game, filename))
		return (0);
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		return (0);
	init_z_buffer(game->z_buffer, WIDTH);
	mouse_init(game);
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
