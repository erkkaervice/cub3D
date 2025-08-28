/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:16:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/26 13:45:40 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_sprite *s, int x, int y)
{
	s->x = x + 0.5f;
	s->y = y + 0.5f;
	s->perp_dist = 0.0f;
	s->texture_id = TEX_SPRITE;
	s->start_x = -1;
	s->end_x = -1;
	s->start_y = -1;
	s->end_y = -1;
	s->dist = 0.0f;
}

void	init_sprite_render(t_game *g, t_sprite *s)
{
	float	inv_det;

	s->sx = s->x - g->player_x;
	s->sy = s->y - g->player_y;
	inv_det = 1.0f / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	s->tx = inv_det * (g->dir_y * s->sx - g->dir_x * s->sy);
	s->ty = inv_det * (-g->plane_y * s->sx + g->plane_x * s->sy);
	if (s->ty <= 0.0001f)
		return ;
	s->screen_x = (int)((WIDTH / 2.0f) * (1.0f + s->tx / s->ty));
	s->height = abs((int)(HEIGHT / s->ty));
	s->width = s->height;
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

	tex = g->textures[TEX_SPRITE];
	dst = (uint32_t *)g->img->pixels;
	x = s->start_x - 1;
	while (++x <= s->end_x)
	{
		if (x < 0 || x >= WIDTH || s->dist >= zb[x])
			continue ;
		y = s->start_y - 1;
		while (++y <= s->end_y)
		{
			if (y < 0 || y >= HEIGHT)
				continue ;
			dst[y * WIDTH + x] = blend_pixel(dst[y * WIDTH + x],
					get_texture_color(g, TEX_SPRITE,
						(x - s->start_x) * tex->width / s->width,
						(y - s->start_y) * tex->height / s->height));
		}
	}
}
