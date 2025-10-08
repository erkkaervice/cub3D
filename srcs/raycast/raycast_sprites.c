/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:36 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 14:05:39 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spr_normalize(float *fx, float *fy)
{
	float	len;

	len = sqrtf((*fx) * (*fx) + (*fy) * (*fy));
	if (len != 0.0f)
	{
		*fx /= len;
		*fy /= len;
	}
}

int	spr_project(t_game *g, t_sprite *s)
{
	float	spx;
	float	spy;
	float	inv_det;

	if (!g || !s)
		return (0);
	spx = s->x - g->player_x;
	spy = s->y - g->player_y;
	inv_det = g->plane_x * g->dir_y - g->dir_x * g->plane_y;
	if (fabsf(inv_det) < SAFE_INV_DET_EPS)
		return (0);
	inv_det = 1.0f / inv_det;
	s->tx = inv_det * (g->dir_y * spx - g->dir_x * spy);
	s->ty = inv_det * (-g->plane_y * spx + g->plane_x * spy);
	if (s->ty <= 0.0f)
		return (0);
	s->perp_dist = s->ty;
	s->screen_x = (int)((g->win_width / 2.0f) * (1.0f + s->tx / s->ty));
	return (1);
}

int	spr_los(const t_game *g, t_sprite *s)
{
	float	dx;
	float	dy;
	float	len;
	float	step;
	float	t;

	if (!g || !s)
		return (0);
	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	len = sqrtf(dx * dx + dy * dy);
	if (len <= 0.0f)
		return (0);
	step = SPRITE_LOS_STEP;
	t = step;
	while (t < len)
	{
		if (tile_blocked(g,
				(int)(s->x + dx * (t / len)),
			(int)(s->y + dy * (t / len))))
			return (0);
		t += step;
	}
	return (1);
}

void	spr_bounds(t_game *g, t_sprite *s)
{
	if (!g || !s)
		return ;
	s->height = (int)fabsf(g->win_height / s->ty);
	if (s->height < 1)
		s->height = 1;
	if (s->height > g->win_height)
		s->height = g->win_height;
	s->width = s->height;
	if (s->width > g->win_width)
		s->width = g->win_width;
	s->start_y = -s->height / 2 + g->win_height / 2;
	if (s->start_y < 0)
		s->start_y = 0;
	s->end_y = s->height / 2 + g->win_height / 2;
	if (s->end_y >= g->win_height)
		s->end_y = g->win_height - 1;
	s->start_x = -s->width / 2 + s->screen_x;
	if (s->start_x < 0)
		s->start_x = 0;
	s->end_x = s->width / 2 + s->screen_x;
	if (s->end_x >= g->win_width)
		s->end_x = g->win_width - 1;
}
