/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:26:52 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_floor_ceiling(t_game *g)
{
	uint32_t	*p;
	int			i;
	uint32_t	floor;
	uint32_t	ceiling;
	int			*rgb;

	p = (uint32_t *)g->frame->pixels;
	rgb = color_atoia(g->cfg->floor_color);
	floor = color_converter(rgb);
	ft_free((char **)&rgb);
	rgb = color_atoia(g->cfg->ceiling_color);
	ceiling = color_converter(rgb);
	ft_free((char **)&rgb);
	i = 0;
	while (i < g->win_width * g->win_height / 2)
		p[i++] = ceiling;
	while (i < g->win_width * g->win_height)
		p[i++] = floor;
}

void	draw_column(t_game *g, t_wall *w, int x, int t)
{
	t_tex	*tex;
	float	step;
	float	p;
	int		y;

	if (t < 0 || t >= TEX_COUNT)
		return ;
	tex = g->tex[t];
	if (!tex || !tex->image || tex->height <= 0)
		return ;
	if (w->draw_start < 0)
		w->draw_start = 0;
	if (w->draw_end >= g->win_height)
		w->draw_end = g->win_height - 1;
	step = (float)tex->height / (float)w->line_height;
	p = (w->draw_start - g->win_height / 2 + w->line_height / 2) * step;
	y = w->draw_start;
	while (y <= w->draw_end)
	{
		blend_pixel(((uint32_t *)g->frame->pixels) + y * g->win_width + x,
			get_tex_color(g, t, w->tex_x, (int)p), &g->z_buffer[x],
			w->perp_wall_dist);
		p += step;
		y++;
	}
}

void	blend_pixel(uint32_t *dst, uint32_t src, float *zbuf, float dist)
{
	uint32_t	dstc;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	a = (src >> 24) & 0xFF;
	if (a == 0)
		return ;
	b = (src >> 16) & 0xFF;
	g = (src >> 8) & 0xFF;
	r = src & 0xFF;
	if (a == 255)
	{
		*dst = 0xFF000000u | (r << 16) | (g << 8) | b;
		*zbuf = dist;
		return ;
	}
	dstc = *dst;
	r = (uint8_t)((r * a + ((dstc >> 16) & 0xFF) * (255 - a)) / 255);
	g = (uint8_t)((g * a + ((dstc >> 8) & 0xFF) * (255 - a)) / 255);
	b = (uint8_t)((b * a + (dstc & 0xFF) * (255 - a)) / 255);
	*dst = 0xFF000000u | (r << 16) | (g << 8) | b;
	if (dist < *zbuf)
		*zbuf = dist;
}

static void	render_game_columns(t_game *g)
{
	int	x;

	x = 0;
	while (x < g->win_width)
	{
		raycast_column(g, x);
		x++;
	}
}

void	render_frame(void *param)
{
	static double	last_time;
	t_game			*g;
	double			current_time;
	double			frame_time;

	g = (t_game *)param;
	current_time = mlx_get_time();
	frame_time = current_time - last_time;
	last_time = current_time;
	fill_floor_ceiling(g);
	update_doors(g);
	apply_mouse_look(g, frame_time);
	update_player_position(g);
	render_game_columns(g);
	render_sprites(g, g->z_buffer);
	if (g->minimap_visible)
		render_minimap(g);
	if (g->fps_visible)
		render_fps(g);
	blit_scaled(g);
}
