/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:28:49 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 18:47:10 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mm_start(char **map)
{
	int		s;
	char	*line;

	if (!map)
		return (0);
	s = 0;
	while (map[s])
	{
		line = map[s];
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == TILE_WALL || *line == TILE_FLOOR || *line == TILE_DOOR)
			break ;
		s++;
	}
	return (s);
}

static int	mm_end(char **map, int start)
{
	int		e;
	char	*line;

	if (!map)
		return (0);
	e = start;
	while (map[e])
	{
		line = map[e];
		while (*line == ' ' || *line == '\t')
			line++;
		if (!(*line == TILE_WALL || *line == TILE_FLOOR || *line == TILE_DOOR))
			break ;
		e++;
	}
	return (e);
}

static void	mm_bounds(t_game *g, int *start, int *end)
{
	if (!g || !g->cfg || !g->cfg->map)
	{
		*start = 0;
		*end = 0;
		return ;
	}
	*start = mm_start(g->cfg->map);
	*end = mm_end(g->cfg->map, *start);
}

static int	mm_width(char **map, int start, int end)
{
	int		w;
	int		len;
	char	*line;

	w = 0;
	while (start < end && map[start])
	{
		line = map[start];
		len = 0;
		while (line[len] && line[len] != '\n')
			len++;
		if (len > w)
			w = len;
		start++;
	}
	return (w);
}

void	mm_render(t_game *g)
{
	int	v[7];

	if (!g || !g->mm_visible || !g->cfg || !g->cfg->map
		|| !g->frame || !g->frame->pixels)
		return ;
	mm_bounds(g, &v[0], &v[1]);
	if (v[1] <= v[0])
		return ;
	v[2] = v[1] - v[0];
	v[3] = mm_width(g->cfg->map, v[0], v[1]);
	if (v[2] <= 0 || v[3] <= 0)
		return ;
	if (v[3] > v[2])
		v[4] = MM_SIZE / v[3];
	else
		v[4] = MM_SIZE / v[2];
	v[5] = g->frame->width;
	v[6] = g->frame->height;
	mm_threads(g, v);
	mm_player(g, v);
	mm_sprites(g, v);
}
