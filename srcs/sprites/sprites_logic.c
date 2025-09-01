/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:16:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/01 16:06:10 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	compute_sprite_transform(t_game *g, t_sprite *s)
{
	float	spx;
	float	spy;
	float	inv_det;

	spx = s->x - g->player_x;
	spy = s->y - g->player_y;
	inv_det = g->plane_x * g->dir_y - g->dir_x * g->plane_y;
	if (fabsf(inv_det) < EPSILON_INV_DET)
		return (0);
	inv_det = 1.0f / inv_det;
	s->tx = inv_det * (g->dir_y * spx - g->dir_x * spy);
	s->ty = inv_det * (-g->plane_y * spx + g->plane_x * spy);
	if (s->ty <= 0.0f)
		return (0);
	s->perp_dist = s->ty;
	s->screen_x = (int)((WIDTH / 2.0f) * (1.0f + s->tx / s->ty));
	return (1);
}

void	compute_sprite_bounds(t_sprite *s)
{
	s->height = (int)fabsf(HEIGHT / s->ty);
	if (s->height < 1)
		s->height = 1;
	if (s->height > HEIGHT)
		s->height = HEIGHT;
	s->width = s->height;
	if (s->width > WIDTH)
		s->width = WIDTH;
	s->start_y = -s->height / 2 + HEIGHT / 2;
	if (s->start_y < 0)
		s->start_y = 0;
	s->end_y = s->height / 2 + HEIGHT / 2;
	if (s->end_y >= HEIGHT)
		s->end_y = HEIGHT - 1;
	s->start_x = -s->width / 2 + s->screen_x;
	if (s->start_x < 0)
		s->start_x = 0;
	s->end_x = s->width / 2 + s->screen_x;
	if (s->end_x >= WIDTH)
		s->end_x = WIDTH - 1;
}

static int	check_los_point(t_game *g, int mx, int my)
{
	return (!is_wall_or_door(g, mx, my));
}

static int	sprite_has_los(t_game *g, t_sprite *s)
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
		if (!check_los_point(g, (int)(s->x + dx * (t / len)),
			(int)(s->y + dy * (t / len))))
			return (0);
		t += step;
	}
	return (1);
}

void	update_sprite(t_game *g, t_sprite *s, float dt)
{
	float		dx;
	float		dy;
	float		len;

	if (!g || !s)
		return ;
	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	len = sqrtf(dx * dx + dy * dy);
	if (len <= SPRITE_STOP_DIST)
	{
		s->stopped = 1;
		s->frame_index = 2;
	}
	else
		s->stopped = 0;
	if (!s->chasing && sprite_has_los(g, s))
		s->chasing = 1;
	if (!s->stopped && s->chasing)
		update_sprite_behavior(g, s, dt);
}
