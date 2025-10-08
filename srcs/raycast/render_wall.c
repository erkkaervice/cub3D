/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:16:58 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 15:02:56 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	col_draw(t_game *g, t_wall *w, int x, int tex_id)
{
	t_tex		*tex;
	float		step;
	float		pos;
	int			y;
	uint32_t	*pixels;

	tex = col_validate(g, w, x, tex_id);
	if (!tex)
		return ;
	pixels = (uint32_t *)g->back_buffer->pixels;
	step = (float)tex->height / (float)w->line_height;
	pos = (w->draw_start - g->win_height / 2 + w->line_height / 2) * step;
	y = w->draw_start - 1;
	while (++y <= w->draw_end)
	{
		blend(&pixels[y * g->back_buffer->width + x],
			tex_color(g, tex_id, w->tex_x, (int)pos),
			&g->z_buffer[x], w->perp_wall_dist);
		pos += step;
	}
}

void	draw_wall(t_game *g, t_ray *r, int x)
{
	t_wall	w;
	t_tex	*tex;
	int		idx;

	wall_calc_bounds(g, r, &w);
	idx = wall_tex_idx(r->side, r->ray_dir_x, r->ray_dir_y);
	tex = g->tex[idx];
	if (!tex || !tex->img)
		return ;
	w.tex_x = wall_tex_x(g, r, w.wall_x, idx);
	draw_tex((t_draw_tex){g, x, &w, tex, idx, 0});
}

t_tex	*col_validate(t_game *g, t_wall *w, int x, int tex_id)
{
	t_tex	*tex;

	if (!g || !g->back_buffer || !g->back_buffer->pixels || !w)
		return (NULL);
	if (tex_id < 0 || tex_id >= TEX_COUNT)
		return (NULL);
	if (x < 0 || x >= g->win_width)
		return (NULL);
	tex = g->tex[tex_id];
	if (!tex || !tex->img || tex->height <= 0)
		return (NULL);
	if (w->draw_start < 0)
		w->draw_start = 0;
	if (w->draw_end >= g->win_height)
		w->draw_end = g->win_height - 1;
	return (tex);
}

void	draw_tex(t_draw_tex args)
{
	int			y;
	float		step;
	float		pos;
	uint32_t	*pixels;
	uint32_t	color;

	step = (float)args.tex->height / (float)args.w->line_height;
	pos = (args.w->draw_start - args.g->win_height
			/ 2 + args.w->line_height / 2) * step;
	y = args.w->draw_start - 1;
	pixels = (uint32_t *)args.g->back_buffer->pixels;
	while (++y <= args.w->draw_end)
	{
		color = 0;
		if (args.w->tex_x + args.shift < args.tex->width
			&& (int)pos < args.tex->height)
			color = tex_color(args.g, args.tex_idx, args.w->tex_x
					+ args.shift, (int)pos);
		if (color)
			blend(&pixels[y * args.g->back_buffer->width + args.x],
				color, &args.g->z_buffer[args.x], args.w->perp_wall_dist);
		pos += step;
	}
}
