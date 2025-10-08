/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_entity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:39:00 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 18:45:25 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mm_entity(t_mm de)
{
	int	half;
	int	dx;
	int	dy;

	if (!de.dst || de.frame_w <= 0 || de.frame_h <= 0)
		return ;
	half = 0;
	if (de.tile_px > 1)
		half = de.tile_px / 4;
	dx = -half;
	while (dx <= half)
	{
		dy = -half;
		while (dy <= half)
		{
			hud_blend((t_hud){de.dst, de.frame_w, de.frame_h,
				de.cx + dy, de.cy + dx, de.color, ENTITY_ALPHA});
			dy++;
		}
		dx++;
	}
}

static void	mm_cone(t_mm dv)
{
	int	a;
	int	i;
	int	len_px;
	int	px;
	int	py;

	if (!dv.dst || dv.frame_w <= 0 || dv.frame_h <= 0)
		return ;
	len_px = dv.tile_px * CONE_WID;
	a = 0;
	while (a < CONE_LEN)
	{
		i = 0;
		while (i < len_px)
		{
			px = dv.cx + (int)(dv.dir_x * cosf(-CONE_OFF + a * CONE_STEP) * i
					- dv.dir_y * sinf(-CONE_OFF + a * CONE_STEP) * i);
			py = dv.cy + (int)(dv.dir_x * sinf(-CONE_OFF + a * CONE_STEP) * i
					+ dv.dir_y * cosf(-CONE_OFF + a * CONE_STEP) * i);
			hud_blend((t_hud){dv.dst, dv.frame_w, dv.frame_h,
				px, py, dv.color, CONE_ALPHA});
			i++;
		}
		a++;
	}
}

static void	mm_sprite(t_game *g, int *v, int idx)
{
	t_mm	de;
	float	fx;
	float	fy;

	de.dst = (uint32_t *)g->frame->pixels;
	de.frame_w = v[5];
	de.frame_h = v[6];
	de.tile_px = v[4];
	de.cx = (int)(g->sprites[idx].x * v[4]);
	de.cy = (int)((g->sprites[idx].y - v[0]) * v[4]);
	de.color = MM_SPRITE;
	mm_entity(de);
	fx = g->sprites[idx].x - g->player_x;
	fy = g->sprites[idx].y - g->player_y;
	spr_normalize(&fx, &fy);
	de.dir_x = -fx;
	de.dir_y = -fy;
	de.color = MM_SPRITE;
	mm_cone(de);
}

void	mm_sprites(t_game *g, int *v)
{
	int	idx;

	if (!g || g->num_sprites <= 0)
		return ;
	idx = 0;
	while (idx < g->num_sprites)
	{
		if (spr_los(g, &g->sprites[idx]))
			mm_sprite(g, v, idx);
		idx++;
	}
}

void	mm_player(t_game *g, int *v)
{
	t_mm	de;

	de.dst = (uint32_t *)g->frame->pixels;
	de.frame_w = v[5];
	de.frame_h = v[6];
	de.tile_px = v[4];
	de.cx = (int)(g->player_x * v[4]);
	de.cy = (int)((g->player_y - v[0]) * v[4]);
	de.color = MM_PLAYER;
	mm_entity(de);
	de.dir_x = g->dir_x;
	de.dir_y = g->dir_y;
	de.color = MM_VIEW;
	mm_cone(de);
}
