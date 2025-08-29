/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:16:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/29 15:41:57 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_game *g, t_sprite *s, int x, int y)
{
	s->x = x + 0.5f;
	s->y = y + 0.5f;
	s->perp_dist = 0.0f;
	s->texture_id = TEX_SPRITE_0;
	s->start_x = -1;
	s->end_x = -1;
	s->start_y = -1;
	s->end_y = -1;
	s->dist = 0.0f;
	s->frame_index = 0;
	s->anim_timer = 0.0f;
	s->speed = 1.5f;
	s->frames[0] = g->textures[TEX_SPRITE_0];
	s->frames[1] = g->textures[TEX_SPRITE_1];
	s->frames[2] = g->textures[TEX_SPRITE_2];
	s->chasing = 0;
}

int	init_sprite_render(t_game *g, t_sprite *s)
{
	float	spriteX;
	float	spriteY;
	float	inv_det;
	float	tx;
	float	ty;

	spriteX = s->x - g->player_x;
	spriteY = s->y - g->player_y;
	inv_det = (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	if (fabsf(inv_det) < 1e-8f)
		return (0);
	inv_det = 1.0f / inv_det;
	tx = inv_det * (g->dir_y * spriteX - g->dir_x * spriteY);
	ty = inv_det * (-g->plane_y * spriteX + g->plane_x * spriteY);
	if (ty <= 0.0f)
		return (0);
	s->tx = tx;
	s->ty = ty;
	s->perp_dist = ty;
	s->screen_x = (int)((WIDTH / 2.0f) * (1.0f + tx / ty));
	s->height = (int)fabsf(HEIGHT / ty);
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
	if (s->perp_dist <= 0.0f)
		return (0);

	return (1);
}

static int	sprite_has_los(t_game *g, t_sprite *s)
{
	float	dx;
	float	dy;
	float	len;
	float	step;
	float	t;
	float	check_x;
	float	check_y;
	int		mx;
	int		my;

	if (!g || !s)
		return (0);
	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	len = sqrtf(dx * dx + dy * dy);
	if (len <= 0.0f)
		return (0);
	step = 0.1f;
	t = step;
	while (t < len)
	{
		check_x = s->x + dx * (t / len);
		check_y = s->y + dy * (t / len);
		mx = (int)check_x;
		my = (int)check_y;
		if (is_wall_or_door(g, mx, my))
			return (0);
		t += step;
	}
	return (1);
}

void	update_sprite(t_game *g, t_sprite *s, float dt)
{
	float	dx;
	float	dy;
	float	len;
	float	move_dist;
	float	nx;
	float	ny;
	const float	stop_dist = 0.5f;
	const float	collision_radius = 0.4f;

	if (!g || !s)
		return ;
	dx = g->player_x - s->x;
	dy = g->player_y - s->y;
	len = sqrtf(dx * dx + dy * dy);
	if (len <= stop_dist)
	{
		s->stopped = 1;
		s->frame_index = 2;
	}
	else
		s->stopped = 0;
	if (!s->chasing && sprite_has_los(g, s))
		s->chasing = 1;
	if (!s->stopped)
	{
		s->anim_timer += dt;
		if (s->anim_timer > 0.2f)
		{
			s->frame_index = (s->frame_index + 1) % 2;
			s->anim_timer = 0.0f;
		}
	}
	if (!s->chasing || s->stopped)
		return ;
	dx /= len;
	dy /= len;
	move_dist = s->speed * dt;
	if (move_dist > len - stop_dist)
		move_dist = len - stop_dist;
	nx = s->x + dx * move_dist;
	ny = s->y + dy * move_dist;
	if (can_move(g, nx + collision_radius, ny + collision_radius) &&
		can_move(g, nx - collision_radius, ny + collision_radius) &&
		can_move(g, nx + collision_radius, ny - collision_radius) &&
		can_move(g, nx - collision_radius, ny - collision_radius))
	{
		s->x = nx;
		s->y = ny;
		return ;
	}
	nx = s->x + dx * move_dist;
	if (can_move(g, nx + collision_radius, s->y + collision_radius) &&
		can_move(g, nx - collision_radius, s->y + collision_radius) &&
		can_move(g, nx + collision_radius, s->y - collision_radius) &&
		can_move(g, nx - collision_radius, s->y - collision_radius))
	{
		s->x = nx;
		return ;
	}
	ny = s->y + dy * move_dist;
	if (can_move(g, s->x + collision_radius, ny + collision_radius) &&
		can_move(g, s->x - collision_radius, ny + collision_radius) &&
		can_move(g, s->x + collision_radius, ny - collision_radius) &&
		can_move(g, s->x - collision_radius, ny - collision_radius))
	{
		s->y = ny;
		return ;
	}
}

static uint32_t	blend_pixel(uint32_t dst_c, uint32_t src_c)
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

void	draw_sprite_stripe(t_game *g, t_sprite *s, float *zb)
{
	t_texture	*tex;
	uint32_t	*dst;
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;

	if (!g || !g->frame || !s)
		return ;
	tex = s->frames[s->frame_index];
	if (!tex || !tex->img || !tex->img->pixels)
		return ;
	dst = (uint32_t *)g->frame->pixels;
	x = s->start_x;
	while (x <= s->end_x)
	{
		if (x < 0 || x >= WIDTH || s->perp_dist >= zb[x])
		{
			x++;
			continue ;
		}
		tex_x = (x - s->start_x) * tex->width / s->width;
		y = s->start_y;
		while (y <= s->end_y)
		{
			if (y >= 0 && y < HEIGHT)
			{
				tex_y = (y - s->start_y) * tex->height / s->height;
				dst[y * WIDTH + x] = blend_pixel(dst[y * WIDTH + x],
					get_texture_color_from_tex(tex, tex_x, tex_y));
			}
			y++;
		}
		x++;
	}
}
