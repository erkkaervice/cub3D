/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:26:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/28 17:53:52 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_tile(t_game *game, t_ray *ray, int map_w, int map_h)
{
	char	tile;
	int		ret;

	if (ray->map_x < 0 || ray->map_x >= map_w
		|| ray->map_y < 0 || ray->map_y >= map_h)
		return (0);
	tile = game->cfg->map[ray->map_y][ray->map_x];
	if (tile == TILE_WALL)
		return (1);
	if (tile == TILE_DOOR)
	{
		ret = handle_door(game, ray);
		if (ret == -1)
			return (-1);
		return (ret);
	}
	return (-1);
}

void	blend_write_pixel(uint32_t *dst, uint32_t src,
	float *zbuf, float dist)
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
