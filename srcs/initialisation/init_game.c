/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 15:47:24 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *g, const char *f)
{
	if (!init_mlx(g))
		return (0);
	if (!init_resources(g, f))
	{
		cleanup_game(g);
		return (0);
	}
	init_mouse(g);
	mlx_cursor_hook(g->mlx, mouse_move, g);
	init_dirs(g);
	init_player(g);
	g->mm_visible = 0;
	g->fps_visible = 0;
	mlx_key_hook(g->mlx, key_input, g);
	mlx_close_hook(g->mlx, app_close, g);
	mlx_loop_hook(g->mlx, draw_frame, g);
	return (1);
}

void	init_arrays(t_game *g)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		g->tex[i] = NULL;
		i++;
	}
	g->input = (t_input){0};
	g->fps.frames = 0;
	g->fps.fps = 0;
	g->fps.last_time = clock();
}

void	init_struct(t_game *g)
{
	g->mlx = NULL;
	g->img = NULL;
	g->frame = NULL;
	g->front_buffer = NULL;
	g->back_buffer = NULL;
	g->cfg = NULL;
	g->player_x = 0.0f;
	g->player_y = 0.0f;
	g->dir_x = 0.0f;
	g->dir_y = 0.0f;
	g->plane_x = 0.0f;
	g->plane_y = 0.0f;
	g->doors = NULL;
	g->num_doors = 0;
	g->sprites = NULL;
	g->num_sprites = 0;
	g->z_buffer = NULL;
	init_arrays(g);
	g->scale_x = SPRITE_DEFAULT_SCALE;
	g->scale_y = SPRITE_DEFAULT_SCALE;
	g->needs_blit = 1;
	g->mm_visible = 0;
	g->fps_visible = 0;
	init_fps(&g->fps, g);
}

void	app_close(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
}

int	init_resources(t_game *g, const char *f)
{
	g->cfg = world_config(f);
	if (!g->cfg || !tex_load_all(g))
	{
		free_cfg(&g->cfg);
		return (0);
	}
	spr_parse(g);
	doors_init(g);
	g->cfg->map_h = 0;
	while (g->cfg->map[g->cfg->map_h])
		g->cfg->map_h++;
	g->cfg->map_w = 0;
	if (g->cfg->map_h > 0)
	{
		while (g->cfg->map[0][g->cfg->map_w])
			g->cfg->map_w++;
	}
	if (!spr_reset(g))
	{
		free_cfg(&g->cfg);
		free_tex(g);
		return (0);
	}
	return (1);
}
