/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:06:35 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 14:05:17 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_move_m(t_game *g, float x, float y, float m)
{
	if (!can_move(g, x, y))
		return (0);
	if (!can_move(g, x + m, y + m))
		return (0);
	if (!can_move(g, x - m, y + m))
		return (0);
	if (!can_move(g, x + m, y - m))
		return (0);
	if (!can_move(g, x - m, y - m))
		return (0);
	return (1);
}

void	move_axis(t_game *g, t_sprite *s, float nx, float ny)
{
	const float	coll = SPRITE_COLLISION_MARGIN;

	if (!s || !g)
		return ;
	if (can_move_m(g, nx, ny, coll))
	{
		s->x = nx;
		s->y = ny;
		return ;
	}
	if (can_move_m(g, nx, s->y, coll))
		s->x = nx;
	if (can_move_m(g, s->x, ny, coll))
		s->y = ny;
}

void	spr_anim(t_sprite *s, float dt)
{
	if (!s)
		return ;
	s->anim_timer += dt;
	if (s->anim_timer > SPRITE_ANIM_INTERVAL)
	{
		s->frame_index++;
		if (s->frame_index > 1)
			s->frame_index = 0;
		s->anim_timer = 0.0f;
	}
}

void	spr_behavior(t_game *g, t_sprite *s, float dt)
{
	float	dx;
	float	dy;
	float	len;
	float	move_dist;
	float	nx;

	if (!s || !g)
		return ;
	spr_anim(s, dt);
	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	len = sqrtf(dx * dx + dy * dy);
	if (len <= SPRITE_STOP_DIST)
		return ;
	dx /= len;
	dy /= len;
	move_dist = s->speed * dt;
	if (move_dist > len - SPRITE_STOP_DIST)
		move_dist = len - SPRITE_STOP_DIST;
	nx = s->x + dx * move_dist;
	move_axis(g, s, nx, s->y + dy * move_dist);
}

void	spr_upd(t_game *g, t_sprite *s, float dt)
{
	float	dx;
	float	dy;
	float	dist_sq;

	if (!g || !s)
		return ;
	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq <= SPRITE_STOP_DIST * SPRITE_STOP_DIST)
	{
		s->stopped = 1;
		s->frame_index = 2;
	}
	else
		s->stopped = 0;
	if (!s->chasing && spr_los(g, s))
		s->chasing = 1;
	if (!s->stopped && s->chasing)
		spr_behavior(g, s, dt);
}
