/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:06:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 14:03:07 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_dim(char **map, int mode)
{
	if (!map)
		return (0);
	if (mode == MAP_DIM_HEIGHT)
		return (ft_array_len((void **)map));
	if (mode == MAP_DIM_WIDTH && map[0])
		return ((int)ft_strlen(map[0]));
	return (0);
}

int	tile_blocked(const t_game *g, int x, int y)
{
	int		w;
	int		h;
	char	t;
	int		d_idx;

	if (!g || !g->cfg || !g->cfg->map)
		return (1);
	h = map_dim(g->cfg->map, MAP_DIM_HEIGHT);
	if (y < 0 || y >= h)
		return (1);
	w = map_dim(&g->cfg->map[y], MAP_DIM_WIDTH);
	if (x < 0 || x >= w)
		return (1);
	t = g->cfg->map[y][x];
	if (t == TILE_WALL)
		return (1);
	if (t == TILE_DOOR)
	{
		d_idx = door_idx(g, x, y);
		return (d_idx < 0 || g->doors[d_idx].open_ratio < DOOR_OPEN_RATIO_FULL);
	}
	return (0);
}
