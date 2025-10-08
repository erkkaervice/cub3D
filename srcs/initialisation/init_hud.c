/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:21:22 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 19:11:42 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_fps(t_fps *fps, t_game *g)
{
	fps->frames = 0;
	fps->fps = 0;
	fps->frame_count = 0;
	fps->g = g;
	fps->x = 0;
	fps->y = 0;
	fps->scale = FPS_SCALE;
	fps->value = 0;
}

void	init_mm(t_game *g, uint32_t *dst, int *v, t_mm_thread *p)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		p[i].g = g;
		p[i].dst = dst;
		p[i].frame_w = v[5];
		p[i].frame_h = v[6];
		p[i].off_x = MM_OFF_X;
		p[i].off_y = MM_OFF_Y;
		p[i].tile_px = v[4];
		p[i].map_start = v[0];
		p[i].start = v[0] + i * ((v[2] + THREADS - 1) / THREADS);
		p[i].end = p[i].start + ((v[2] + THREADS - 1) / THREADS);
		if (p[i].start >= v[1])
		{
			p[i].start = v[1];
			p[i].end = v[1];
		}
		else if (p[i].end > v[1])
			p[i].end = v[1];
		i++;
	}
}

void	init_dirs(t_game *g)
{
	g->dir_infos[0] = (t_dir_info){DIR_NORTH_CHAR, DIR_NORTH_X, DIR_NORTH_Y,
		DIR_NORTH_PLANE_X, DIR_NORTH_PLANE_Y};
	g->dir_infos[1] = (t_dir_info){DIR_SOUTH_CHAR, DIR_SOUTH_X, DIR_SOUTH_Y,
		DIR_SOUTH_PLANE_X, DIR_SOUTH_PLANE_Y};
	g->dir_infos[2] = (t_dir_info){DIR_EAST_CHAR, DIR_EAST_X, DIR_EAST_Y,
		DIR_EAST_PLANE_X, DIR_EAST_PLANE_Y};
	g->dir_infos[3] = (t_dir_info){DIR_WEST_CHAR, DIR_WEST_X, DIR_WEST_Y,
		DIR_WEST_PLANE_X, DIR_WEST_PLANE_Y};
}

void	init_player(t_game *g)
{
	int	i;

	g->player_x = g->cfg->player_x + RAY_HALF_TILE_OFFSET;
	g->player_y = g->cfg->player_y + RAY_HALF_TILE_OFFSET;
	i = 0;
	while (i < DIR_COUNT)
	{
		if (g->dir_infos[i].dir == g->cfg->player_dir)
		{
			g->dir_x = g->dir_infos[i].dir_x;
			g->dir_y = g->dir_infos[i].dir_y;
			g->plane_x = g->dir_infos[i].plane_x;
			g->plane_y = g->dir_infos[i].plane_y;
			return ;
		}
		i++;
	}
}

void	init_mouse(t_game *g)
{
	g->mouse.dx = 0.0;
	g->mouse.sensitivity = MOUSE_SENSITIVITY;
	g->mouse.prev_x = g->frame->width / 2;
	mlx_set_cursor_mode(g->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(g->mlx,
		g->frame->width / 2, g->frame->height / 2);
}
