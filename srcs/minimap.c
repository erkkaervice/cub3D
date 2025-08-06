/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:16:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/06 15:58:28 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
	uint32_t	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (uint32_t *)game->img->pixels + y * WIDTH + x;
	*pixel = color;
}

static void	draw_minimap_tile(t_game *game, int map_x, int map_y)
{
	int		px;
	int		py;
	int		i;
	int		j;
	int		color;

	px = map_x * MINIMAP_SCALE;
	py = map_y * MINIMAP_SCALE;
	if (game->cfg->map[map_y][map_x] == '1')
		color = MINIMAP_WALL_COLOR;
	else
		color = MINIMAP_FLOOR_COLOR;
	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			draw_minimap_pixel(game, px + i, py + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_player_minimap(t_game *game)
{
	int		px;
	int		py;
	int		size;
	int		i;
	int		j;

	size = MINIMAP_SCALE / 2;
	px = (int)(game->player_x * MINIMAP_SCALE);
	py = (int)(game->player_y * MINIMAP_SCALE);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_minimap_pixel(game, px + i, py + j, MINIMAP_PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	map_x;
	int	map_y;

	map_y = 0;
	while (game->cfg->map[map_y])
	{
		map_x = 0;
		while (game->cfg->map[map_y][map_x])
		{
			draw_minimap_tile(game, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
	draw_player_minimap(game);
}
