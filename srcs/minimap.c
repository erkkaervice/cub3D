/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:16:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/25 16:22:15 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_pixel(t_game *g, int x, int y, int color)
{
	uint32_t	*px;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	px = (uint32_t *)g->img->pixels + y * WIDTH + x;
	*px = color;
}

static void	draw_tile(t_game *g, int x, int y, char tile)
{
	int	i;
	int	j;
	int	c;

	if (tile == TILE_WALL)
		c = MINIMAP_WALL_COLOR;
	else if (tile == TILE_DOOR)
		c = MINIMAP_DOOR_COLOR;
	else if (tile == TILE_SPRITE)
		c = MINIMAP_SPRITE_COLOR;
	else
		c = MINIMAP_FLOOR_COLOR;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			draw_pixel(g, x * MINIMAP_SCALE + i, y * MINIMAP_SCALE + j, c);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *g, int map_start_y)
{
	int	i;
	int	j;
	int	size;
	int	px;
	int	py;

	size = MINIMAP_SCALE / 2;
	px = (int)(g->player_x * MINIMAP_SCALE);
	py = (int)((g->player_y - map_start_y) * MINIMAP_SCALE);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(g, px + i, py + j, MINIMAP_PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *g)
{
	int	y;
	int	x;
	int	start;
	int	end;
	int	row_y;

	start = 0;
	while (g->cfg->map[start])
	{
		if (g->cfg->map[start][0] == TILE_WALL
			|| g->cfg->map[start][0] == TILE_FLOOR
			|| g->cfg->map[start][0] == TILE_DOOR
			|| g->cfg->map[start][0] == TILE_SPRITE)
			break ;
		start++;
	}
	end = start;
	while (g->cfg->map[end])
	{
		if (g->cfg->map[end][0] != TILE_WALL
			&& g->cfg->map[end][0] != TILE_FLOOR
			&& g->cfg->map[end][0] != TILE_DOOR
			&& g->cfg->map[end][0] != TILE_SPRITE)
			break ;
		end++;
	}
	row_y = 0;
	y = start;
	while (y < end)
	{
		x = 0;
		while (g->cfg->map[y][x] && g->cfg->map[y][x] != '\n')
		{
			if (g->cfg->map[y][x] == TILE_WALL
				|| g->cfg->map[y][x] == TILE_FLOOR
				|| g->cfg->map[y][x] == TILE_DOOR
				|| g->cfg->map[y][x] == TILE_SPRITE)
				draw_tile(g, x, row_y, g->cfg->map[y][x]);
			x++;
		}
		row_y++;
		y++;
	}
	draw_player(g, start);
}
