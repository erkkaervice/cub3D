/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:26:13 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/25 15:31:18 by eala-lah         ###   ########.fr       */
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
