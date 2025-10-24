/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:12:46 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/24 16:18:59 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spr_pixel(t_game *g, int xi, int y, uint32_t color)
{
	uint32_t	*dst;
	float		z;

	if (!g || !g->frame)
		return ;
	dst = (uint32_t *)g->frame->pixels;
	z = 0.0f;
	blend(&dst[y * g->frame->width + xi], color, &z, 0.0f);
}

void	spr_col(t_game *g, t_sprite *s, int xi)
{
	t_tex		*t;
	int			y;
	int			tx;
	uint32_t	color;

	if (!s || !s->frames[s->frame_index])
		return ;
	t = s->frames[s->frame_index];
	if (!t || !t->tex || !t->tex->pixels || s->width <= 0 || s->height <= 0)
		return ;
	if (xi < s->start_x || xi > s->end_x)
		return ;
	tx = (xi - s->start_x) * t->width / s->width;
	y = s->start_y;
	if (y < 0)
		y = 0;
	while (y <= s->end_y && y < g->win_height)
	{
		color = tex_pixel(t, tx,
				(int)((y - s->start_y) * (float)t->height / s->height));
		spr_pixel(g, xi, y, color);
		y++;
	}
}

void	spr_stripe(t_game *g, t_sprite *s, float *zb)
{
	int	x;
	int	xi;
	int	start_x;
	int	end_x;
	int	fw;

	if (!g || !g->frame || !s || !zb)
		return ;
	fw = g->frame->width;
	start_x = s->start_x;
	if (start_x < 0)
		start_x = 0;
	end_x = s->end_x;
	if (end_x >= g->win_width)
		end_x = g->win_width - 1;
	x = start_x;
	while (x <= end_x)
	{
		xi = x * fw / g->win_width;
		if (xi >= 0 && xi < fw && s->perp_dist < zb[xi])
			spr_col(g, s, xi);
		x++;
	}
}

void	sort_spr(t_game *g)
{
	int			i;
	int			j;
	t_sprite	key;

	if (!g || !g->sprites || g->num_sprites <= 0)
		return ;
	i = 1;
	while (i < g->num_sprites)
	{
		key = g->sprites[i];
		j = i - 1;
		while (j >= 0 && g->sprites[j].dist < key.dist)
		{
			g->sprites[j + 1] = g->sprites[j];
			j--;
		}
		g->sprites[j + 1] = key;
		i++;
	}
}

void	spr_render(t_game *g, float *zb, float dt)
{
	pthread_t		threads[THREADS];
	t_sprite_thread	params[THREADS];
	int				i;

	if (!g || !zb || !g->sprites || g->num_sprites <= 0)
		return ;
	start_spr_threads(g, zb, dt, params);
	sort_spr(g);
	i = 0;
	while (i < THREADS)
	{
		pthread_create(&threads[i], NULL, spr_thread, &params[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
}
