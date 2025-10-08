/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:01:44 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 15:02:56 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_draw_bg(t_game *g, t_ray *r, int x)
{
	t_ray	r2;
	t_wall	w;
	t_tex	*tex;
	int		idx;
	int		hit;

	r2 = *r;
	hit = raycast_dda(g, &r2, x);
	if (hit == RAY_HIT_NONE)
		return ;
	wall_calc_bounds(g, &r2, &w);
	if (hit == RAY_HIT_WALL)
		idx = wall_tex_idx(r2.side, r2.ray_dir_x, r2.ray_dir_y);
	else
		idx = TEX_DOOR;
	tex = g->tex[idx];
	if (!tex || !tex->img)
		return ;
	w.tex_x = wall_tex_x(g, &r2, w.wall_x, idx);
	draw_tex((t_draw_tex){g, x, &w, tex, idx, 0});
}

void	door_draw_col(t_game *g, t_ray *r, int x)
{
	t_wall		w;
	t_tex		*tex;
	t_draw_tex	dt;
	int			d_idx;
	int			shift;

	wall_calc_bounds(g, r, &w);
	d_idx = door_idx(g, r->map_x, r->map_y);
	shift = 0;
	if (d_idx >= 0)
		shift = (int)(g->doors[d_idx].open_ratio * g->tex[TEX_DOOR]->width);
	tex = g->tex[TEX_DOOR];
	if (!tex || !tex->img)
		return ;
	w.tex_x = wall_tex_x(g, r, w.wall_x, TEX_DOOR);
	dt = (t_draw_tex){g, x, &w, tex, TEX_DOOR, shift};
	if (shift > 0)
		door_draw_bg(g, r, x);
	draw_tex(dt);
}

int	door_idx(const t_game *g, int x, int y)
{
	int	i;

	if (!g || !g->doors)
		return (-1);
	i = 0;
	while (i < g->num_doors)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}
