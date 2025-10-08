/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_layer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:29:00 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 19:17:24 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mm_valid(t_mm_thread *t, int x, int y, char *ch)
{
	int	line_len;

	if (!t || !t->g || !t->g->cfg || !t->g->cfg->map || !t->g->cfg->map[y])
		return (0);
	line_len = 0;
	while (t->g->cfg->map[y][line_len] && t->g->cfg->map[y][line_len] != '\n')
		line_len++;
	if (x < 0 || x >= line_len)
		return (0);
	*ch = t->g->cfg->map[y][x];
	if (!ft_strchr(MAP_CHARS, *ch))
		return (0);
	return (1);
}

static void	mm_cell(t_mm dt, int bx, int by)
{
	int			i;
	int			j;
	uint32_t	color;

	if (dt.tile == TILE_WALL)
		color = MM_WALL;
	else if (dt.tile == TILE_DOOR)
		color = MM_DOOR;
	else
		color = MM_FLOOR;
	i = 0;
	while (i < dt.tile_px)
	{
		j = 0;
		while (j < dt.tile_px)
		{
			if ((bx + j >= 0 && bx + j < dt.frame_w)
				&& (by + i >= 0 && by + i < dt.frame_h))
				hud_blend((t_hud){dt.dst, dt.frame_w, dt.frame_h,
					bx + j, by + i, color, 0.5f});
			j++;
		}
		i++;
	}
}

static void	mm_tile(t_mm_thread *t, uint32_t *dst, int x, int y)
{
	t_mm	dt;
	char	ch;
	int		bx;
	int		by;

	if (!mm_valid(t, x, y, &ch))
		return ;
	dt.dst = dst;
	dt.frame_w = t->frame_w;
	dt.frame_h = t->frame_h;
	dt.off_x = t->off_x;
	dt.off_y = t->off_y;
	dt.tile_px = t->tile_px;
	if (dt.tile_px <= 0)
		dt.tile_px = 1;
	dt.tx = x;
	dt.ty = y - t->map_start;
	dt.tile = ch;
	bx = dt.off_x + dt.tx * dt.tile_px;
	by = dt.off_y + dt.ty * dt.tile_px;
	mm_cell(dt, bx, by);
}

static void	*mm_thread(void *arg)
{
	t_mm_thread	*t;
	uint32_t	*dst;
	int			y;
	int			x;

	t = (t_mm_thread *)arg;
	if (!t || !t->g || !t->g->cfg || !t->g->cfg->map)
		return (NULL);
	dst = t->dst;
	y = t->start;
	while (y < t->end && t->g->cfg->map[y])
	{
		x = 0;
		while (t->g->cfg->map[y][x] && t->g->cfg->map[y][x] != '\n')
		{
			mm_tile(t, dst, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	mm_threads(t_game *g, int *v)
{
	t_mm_thread	params[THREADS];
	pthread_t	threads[THREADS];
	int			i;
	uint32_t	*dst;
	int			map_rows;

	if (!g || !g->cfg || !g->cfg->map || !g->frame || !g->frame->pixels)
		return ;
	dst = (uint32_t *)g->frame->pixels;
	map_rows = 0;
	while (g->cfg->map[map_rows])
		map_rows++;
	init_mm(g, dst, v, params);
	i = 0;
	while (i < THREADS)
	{
		if (params[i].end > map_rows)
			params[i].end = map_rows;
		pthread_create(&threads[i], NULL, mm_thread, &params[i]);
		if (params[i].start < params[i].end)
			pthread_join(threads[i], NULL);
		i++;
	}
}
