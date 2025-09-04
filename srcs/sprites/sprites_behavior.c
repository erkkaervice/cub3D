/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_behavior.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:54:49 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 20:00:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_sprite_axis(t_game *g, t_sprite *s, float nx, float ny)
{
	const float	coll = SPRITE_COLLISION_MARGIN;
	float		check_x[2];
	float		check_y[2];

	check_x[0] = nx - coll;
	check_x[1] = nx + coll;
	check_y[0] = ny - coll;
	check_y[1] = ny + coll;
	if (can_move(g, nx, ny)
		&& can_move(g, check_x[1], check_y[1])
		&& can_move(g, check_x[0], check_y[1])
		&& can_move(g, check_x[1], check_y[0])
		&& can_move(g, check_x[0], check_y[0]))
	{
		s->x = nx;
		s->y = ny;
	}
}

void	update_sprite_behavior(t_game *g, t_sprite *s, float dt)
{
	float	dx;
	float	dy;
	float	len;
	float	move_dist;

	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	s->anim_timer += dt;
	if (s->anim_timer > SPRITE_ANIM_INTERVAL)
	{
		s->frame_index = (s->frame_index + 1) % 2;
		s->anim_timer = 0.0f;
	}
	len = sqrtf(dx * dx + dy * dy);
	if (len <= SPRITE_STOP_DIST)
		return ;
	dx /= len;
	dy /= len;
	move_dist = s->speed * SPRITE_FRAME_DT;
	if (move_dist > len - SPRITE_STOP_DIST)
		move_dist = len - SPRITE_STOP_DIST;
	move_sprite_axis(g, s, s->x + dx * move_dist, s->y + dy * move_dist);
	move_sprite_axis(g, s, s->x + dx * move_dist, s->y);
	move_sprite_axis(g, s, s->x, s->y + dy * move_dist);
}

static uint32_t	blend_color(uint32_t dst_c, uint32_t src_c)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	gc;
	uint8_t	b;

	a = (src_c >> 24) & 0xFF;
	r = (src_c) & 0xFF;
	gc = (src_c >> 8) & 0xFF;
	b = (src_c >> 16) & 0xFF;
	if (a == 0)
		return (dst_c);
	if (a == 255)
		return (0xFF000000u | (r << 16) | (gc << 8) | b);
	r = (uint8_t)((r * a + ((dst_c >> 16) & 0xFF) * (255 - a)) / 255);
	gc = (uint8_t)((gc * a + ((dst_c >> 8) & 0xFF) * (255 - a)) / 255);
	b = (uint8_t)((b * a + (dst_c & 0xFF) * (255 - a)) / 255);
	return (0xFF000000u | (r << 16) | (gc << 8) | b);
}

static void	draw_sprite_column(t_sprite *s, int x, uint32_t *dst, t_game *g)
{
	t_tex	*t;
	int		y;
	int		tex_x;
	int		tex_y;

	t = s->frames[s->frame_index];
	if (!t || !t->img || !t->img->pixels)
		return ;
	tex_x = (x - s->start_x) * t->width / s->width;
	y = s->start_y;
	while (y <= s->end_y)
	{
		if (y >= 0 && y < (int)g->win_height)
		{
			tex_y = (y - s->start_y) * t->height / s->height;
			dst[y * g->win_width + x] = blend_color(dst[y * g->win_width + x],
					get_tex_color_from_tex(t, tex_x, tex_y));
		}
		y++;
	}
}

void	draw_sprite_stripe(t_game *g, t_sprite *s, float *zb)
{
	uint32_t	*dst;
	int			x;

	if (!g || !g->frame || !s || !zb)
		return ;
	dst = (uint32_t *)g->frame->pixels;
	x = s->start_x;
	while (x <= s->end_x)
	{
		if (x >= 0 && x < g->win_width && s->perp_dist < zb[x])
			draw_sprite_column(s, x, dst, g);
		x++;
	}
}
