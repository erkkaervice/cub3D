/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:42:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/08 17:13:53 by eala-lah         ###   ########.fr       */
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
	float	*new_zbuf;

	game = (t_game *)param;
	if (w <= 0 || h <= 0)
		return ;
	game->win_width = w;
	game->win_height = h;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, w, h);
	if (!game->img)
		exit(1);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		exit(1);
	new_zbuf = ft_calloc(w, sizeof(float));
	if (!new_zbuf)
		exit(1);
	if (game->z_buffer)
		free(game->z_buffer);
	game->z_buffer = new_zbuf;
	game->needs_blit = 1;
}

static int	init_mlx_win_and_img(t_game *g)
{
	g->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (!g->mlx)
		return (0);
	g->frame = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	g->img = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->frame || !g->img
		|| mlx_image_to_window(g->mlx, g->img, 0, 0) < 0)
	{
		if (g->img)
			mlx_delete_image(g->mlx, g->img);
		if (g->frame)
			mlx_delete_image(g->mlx, g->frame);
		mlx_terminate(g->mlx);
		return (0);
	}
	g->win_width = WINDOW_WIDTH;
	g->win_height = WINDOW_HEIGHT;
	g->needs_blit = 1;
	mlx_resize_hook(g->mlx, resize_hook, g);
	return (1);
}

static int	init_game_resources(t_game *g, char *f)
{
	int	i;

	g->cfg = map_config(f);
	if (!g->cfg || !load_tex(g))
	{
		free_partial_config(&g->cfg);
		return (0);
	}
	parse_sprites(g);
	init_doors(g);
	g->z_buffer = ft_calloc(g->win_width, sizeof(float));
	if (!g->z_buffer)
	{
		free_partial_config(&g->cfg);
		free_tex(g, TEX_COUNT);
		return (0);
	}
	i = 0;
	while (i < g->win_width)
	{
		g->z_buffer[i] = 0.0f;
		i++;
	}
	return (1);
}

int	init_game(t_game *g, char *f)
{
	if (!init_mlx_win_and_img(g))
		return (0);
	if (!init_game_resources(g, f))
	{
		cleanup_game(g);
		return (0);
	}
	init_mouse(g);
	mlx_cursor_hook(g->mlx, mouse_move, g);
	init_dir_infos(g);
	init_player(g);
	g->minimap_visible = 0;
	g->fps_visible = 0;
	mlx_key_hook(g->mlx, key_hook, g);
	mlx_close_hook(g->mlx, close_hook, g);
	mlx_loop_hook(g->mlx, render_frame, g);
	return (1);
}
