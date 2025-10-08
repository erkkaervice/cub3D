/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:11:48 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 15:02:56 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_tex_idx(int side, float ray_dir_x, float ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (TEX_EAST);
		return (TEX_WEST);
	}
	if (ray_dir_y > 0)
		return (TEX_SOUTH);
	return (TEX_NORTH);
}

int	wall_tex_x(const t_game *g, const t_ray *r, float wall_x, int tex_id)
{
	int			tex_x;
	t_tex		*t;

	if (tex_id < 0 || tex_id >= TEX_COUNT)
		return (0);
	t = g->tex[tex_id];
	if (!t || !t->img)
		return (0);
	tex_x = (int)(wall_x * (float)t->width);
	if ((r->side == AXIS_X && r->ray_dir_x > 0)
		|| (r->side == AXIS_Y && r->ray_dir_y < 0))
		tex_x = t->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= t->width)
		tex_x = t->width - 1;
	return (tex_x);
}

float	wall_calc_perp(const t_game *g, t_ray *r, float *wx)
{
	float	perp;
	float	offset;

	offset = (1 - r->step_x) * RAY_HALF_TILE_OFFSET;
	if (r->side == AXIS_X)
	{
		perp = (r->map_x - g->player_x + offset) / r->ray_dir_x;
		*wx = g->player_y + perp * r->ray_dir_y;
	}
	else
	{
		offset = (1 - r->step_y) * RAY_HALF_TILE_OFFSET;
		perp = (r->map_y - g->player_y + offset) / r->ray_dir_y;
		*wx = g->player_x + perp * r->ray_dir_x;
	}
	if (perp < RAY_MIN_PERP_DIST)
		perp = RAY_MIN_PERP_DIST;
	*wx -= floorf(*wx);
	return (perp);
}

void	wall_calc_bounds(const t_game *g, const t_ray *r, t_wall *w)
{
	float	perp;
	int		h;
	int		half_height;
	int		ds;
	float	wx;

	if (!g || !r || !w || !g->frame)
		return ;
	perp = wall_calc_perp(g, (t_ray *)r, &wx);
	h = (int)((float)g->frame->height / perp);
	if (h < 1)
		h = 1;
	half_height = g->frame->height / 2;
	ds = -h / 2 + half_height;
	if (ds < 0)
		ds = 0;
	w->perp_wall_dist = perp;
	w->line_height = h;
	w->draw_start = ds;
	w->draw_end = h / 2 + half_height;
	if (w->draw_end >= (int)g->frame->height)
		w->draw_end = g->frame->height - 1;
	w->wall_x = wx;
}
